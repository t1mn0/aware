include(GoogleTest)

set(ITERATOR_TESTS
    iter_patterns
    unit
)

foreach(ITERATOR_TEST ${ITERATOR_TESTS})
    add_executable(${ITERATOR_TEST} ${ITERATOR_TEST}.cpp)
    target_link_libraries(${ITERATOR_TEST} PRIVATE aware_meta aware_ds GTest::gtest_main)
    gtest_discover_tests(${ITERATOR_TEST})
endforeach()
