#include "abi.hpp"

#include <cstddef>

#include "arch/x86_64/cpu.hpp"

namespace abi {

extern "C" {
void *__dso_handle = nullptr;
int __cxa_atexit(void (*)(void *), void *, void *) { return 0; }
void __cxa_pure_virtual() { arch::x86_64::hcf(); }
}

void init_global_constructor() {
  for (std::size_t i = 0; &__init_array[i] != __init_array_end; i++) {
    __init_array[i]();
  }
}

} // namespace abi
