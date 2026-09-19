# Kernel build configuration

# Define the kernel executable
add_executable(kernel)

# Modular source organization
# target_sources(kernel PRIVATE
#     src/boot/main.cpp
# )
#
# # Core module
# target_sources(kernel PRIVATE
#     src/core/kernel.cpp
#     src/core/kernel.h
# )

# Render module
# target_sources(kernel PRIVATE
#     src/render/BasicRenderer.cpp
#     src/render/BasicRenderer.hpp
# )
#
# Include directories

file(GLOB_RECURSE KERNEL_SOURCES  "./src/*.c" "./src/*.cpp")

target_sources(kernel PRIVATE ${KERNEL_SOURCES})

target_include_directories(kernel PRIVATE
    src
    include
)

# Link external dependencies
target_link_libraries(kernel PRIVATE
    freestnd-c
    freestnd-cxx
    limine-protocol
    cc-runtime
)

# Set kernel specific properties
set_target_properties(kernel PROPERTIES
    OUTPUT_NAME kernel
    LINK_DEPENDS "${LINKER_SCRIPT}"
)

# Apply compiler options
target_compile_options(kernel PRIVATE 
    ${ARCH_FLAGS} 
    ${KERNEL_COMPILE_OPTIONS}
    $<$<COMPILE_LANGUAGE:CXX>:${KERNEL_CXX_COMPILE_OPTIONS}>
)

# Apply linker options
target_link_options(kernel PRIVATE
    ${ARCH_LINKER_FLAGS}
    ${KERNEL_LINK_OPTIONS}
    "-T${LINKER_SCRIPT}"
)
