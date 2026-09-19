#pragma once

#include "limine.h"
#include <stddef.h>

namespace {

[[gnu::used,
  gnu::section(".limine_requests")]] volatile uint64_t base_revision[] =
    LIMINE_BASE_REVISION(4);

[[gnu::used, gnu::section(".limine_requests")]]
volatile limine_framebuffer_request framebuffer_request = {
    LIMINE_FRAMEBUFFER_REQUEST_ID, 0, nullptr};

[[gnu::used, gnu::section(".limine_requests")]]
volatile limine_hhdm_request hhdm_request = {LIMINE_HHDM_REQUEST_ID, 0,
                                             nullptr};

[[gnu::used, gnu::section(".limine_requests")]]
volatile limine_memmap_request memmap_request = {LIMINE_MEMMAP_REQUEST_ID, 0,
                                                 nullptr};

[[gnu::used, gnu::section(".limine_requests")]]
volatile limine_executable_address_request executable_address_request = {
    LIMINE_EXECUTABLE_ADDRESS_REQUEST_ID, 0, nullptr};

[[gnu::used, gnu::section(".limine_requests")]]
volatile limine_rsdp_request rsdp_request = {LIMINE_RSDP_REQUEST_ID, 0,
                                             nullptr};
[[gnu::used, gnu::section(".limine_requests")]]
volatile limine_module_request module_request = {LIMINE_MODULE_REQUEST_ID, 0,
                                                 nullptr, 0, nullptr};

[[gnu::used, gnu::section(".limine_requests_start")]]
volatile uint64_t limine_requests_start_marker[] = LIMINE_REQUESTS_START_MARKER;

[[gnu::used, gnu::section(".limine_requests_end")]]
volatile uint64_t limine_requests_end_marker[] = LIMINE_REQUESTS_END_MARKER;

} // namespace
