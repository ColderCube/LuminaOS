#include "lib/limine_helper.hpp"

#include "arch/x86_64/cpu.hpp"
#include "lib/string.h"

namespace limine_helper {

struct limine_file *
getFile(const char *name,
        const volatile limine_module_request &module_request) {
  struct limine_module_response *module_response = module_request.response;

  if (module_response == nullptr) {
    arch::x86_64::hcf();
  }

  for (size_t i = 0; i < module_response->module_count; i++) {
    struct limine_file *f = module_response->modules[i];
    if (checkStringEndsWith(f->path, name))
      return f;
  }

  return nullptr;
}

} // namespace limine_helper
