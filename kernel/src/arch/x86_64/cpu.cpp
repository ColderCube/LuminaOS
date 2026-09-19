#include "arch/x86_64/cpu.hpp"

namespace arch::x86_64 {

[[noreturn]] void hcf() {
  for (;;) {
    asm("hlt");
  }
}

} // namespace arch::x86_64
