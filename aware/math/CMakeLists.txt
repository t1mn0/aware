add_library(aware_math INTERFACE)

target_include_directories(aware_math INTERFACE
    $<BUILD_INTERFACE:${AWARE_ROOT_DIR}>
)

target_sources(aware_ds INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/concepts/multiplicative.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/power/power.hpp
)
