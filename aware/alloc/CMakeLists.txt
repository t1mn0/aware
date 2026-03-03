add_library(aware_alloc INTERFACE)

target_include_directories(aware_alloc INTERFACE
    $<BUILD_INTERFACE:${AWARE_ROOT_DIR}>
)

target_link_libraries(aware_alloc INTERFACE eav)

target_sources(aware_alloc INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/alloc_interface.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/memory_resource.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/memory_provider/interface.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/memory_provider/malloc_provider.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/linear/allocator.hpp
)
