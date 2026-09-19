#pragma once


extern void (*__init_array[])();
extern void (*__init_array_end[])();

namespace abi {

extern "C" {
int __cxa_atexit(void (*)(void *), void *, void *);
void __cxa_pure_virtual();
extern void *__dso_handle;
}

// Extern declarations for global constructors array.

void init_global_constructor();

}
