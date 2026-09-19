#include <cstddef>
#include <cstdint>
#include <limine.h>

#include "abi.hpp"
#include "arch/x86_64/cpu.hpp"
#include "boot/limine_requests.hpp"
#include "core/kernel.h"
#include "lib/limine_helper.hpp"
#include "lib/string.h"

using namespace arch::x86_64;

// bool checkStringEndsWith(const char *str, const char *end) {
//   const char *_str = str;
//   const char *_end = end;
//
//   while (*str != 0)
//     str++;
//   str--;
//
//   while (*end != 0)
//     end++;
//   end--;
//
//   while (true) {
//     if (*str != *end)
//       return false;
//
//     str--;
//     end--;
//
//     if (end == _end || (str == _str && end == _end))
//       return true;
//
//     if (str == _str)
//       return false;
//   }
//
//   return true;
// }

// The following stubs are required by the Itanium C++ ABI (the one we use,
// regardless of the "Itanium" nomenclature).
// Like the memory functions above, these stubs can be moved to a different .cpp
// file, but should not be removed, unless you know what you are doing.
// extern "C" {
// int __cxa_atexit(void (*)(void *), void *, void *) { return 0; }
// void __cxa_pure_virtual() { hcf(); }
// void *__dso_handle;
// }
//
// // Extern declarations for global constructors array.
// extern void (*__init_array[])();
// extern void (*__init_array_end[])();

// The following will be our kernel's entry point.
// If renaming kmain() to something else, make sure to change the
// linker script accordingly.
extern "C" void kmain() {
  // Ensure the bootloader actually understands our base revision (see spec).
  if (LIMINE_BASE_REVISION_SUPPORTED(base_revision) == false) {
    hcf();
  }

  // Call global constructors.
  abi::init_global_constructor();
  // for (std::size_t i = 0; &__init_array[i] != __init_array_end; i++) {
  //   __init_array[i]();
  // }

  // Ensure we got a framebuffer.
  if (framebuffer_request.response == nullptr ||
      framebuffer_request.response->framebuffer_count < 1) {
    hcf();
  }

  // Fetch the first framebuffer.
  limine_framebuffer *framebuffer =
      framebuffer_request.response->framebuffers[0];

  struct Framebuffer fb;
  {
    fb.base_address = framebuffer->address;
    fb.width = framebuffer->width;
    fb.height = framebuffer->height;
    fb.pixels_per_scan_line = framebuffer->pitch / 4;
    fb.buffer_size = framebuffer->height * framebuffer->pitch;
  }

  struct PSF1_FONT font;
  {
    const char *fName = "zap-light16.psf";
    struct limine_file *file = limine_helper::getFile(fName, module_request);
    if (file == NULL) {
      hcf();
    }

    font.psf1_header = (struct PSF1_HEADER *)file->address;
    if (font.psf1_header->magic[0] != 0x36 ||
        font.psf1_header->magic[1] != 0x04) {
      hcf();
    }

    font.glyph_buffer =
        (void *)((uint64_t)file->address + sizeof(struct PSF1_HEADER));
  }

  kernel(fb, &font);

  // Note: we assume the framebuffer model is RGB with 32-bit pixels.
  /*for (std::size_t i = 0; i < 100; i++) {
      volatile std::uint32_t *fb_ptr = static_cast<volatile std::uint32_t
  *>(framebuffer->address); fb_ptr[i * (framebuffer->pitch / 4) + i] =
  0xffffff;
  }*/

  // We're done, just hang...
  arch::x86_64::hcf();
}
