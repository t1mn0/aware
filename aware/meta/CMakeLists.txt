add_library(aware_meta INTERFACE)

target_include_directories(aware_meta INTERFACE
    $<BUILD_INTERFACE:${AWARE_ROOT_DIR}>
)

target_sources(aware_meta INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/conditional.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/constants/integral.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/constants/bool.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/decorate/remove_cv.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/verify/is_same.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/verify/is_void.hpp
)
