add_library(aware_ds INTERFACE)

target_include_directories(aware_ds INTERFACE
    $<BUILD_INTERFACE:${AWARE_ROOT_DIR}>
)

target_link_libraries(aware_ds INTERFACE aware_meta eav)

target_sources(aware_ds INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/vector.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/iterator/common_iterator.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/iterator/cursor.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/iterator/tag.hpp
)
