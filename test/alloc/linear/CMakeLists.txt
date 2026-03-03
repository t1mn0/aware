include(GoogleTest)

set(LINEAR_ALLOCATOR_TESTS
    alloc_unit
)

foreach(LINEAR_ALLOCATOR_TEST ${LINEAR_ALLOCATOR_TESTS})
    add_executable(${LINEAR_ALLOCATOR_TEST} ${LINEAR_ALLOCATOR_TEST}.cpp)
    target_link_libraries(${LINEAR_ALLOCATOR_TEST} PRIVATE aware_alloc GTest::gtest_main)
    gtest_discover_tests(${LINEAR_ALLOCATOR_TEST})
endforeach()
