cmake_minimum_required(VERSION 3.20)
project(aware LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(AWARE_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(2ndparty)
add_subdirectory(3rdparty)
add_subdirectory(aware/meta)
add_subdirectory(aware/ds)
add_subdirectory(aware/math)

enable_testing()
add_subdirectory(test)
