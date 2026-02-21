include(GoogleTest)

set(ITERATOR_TESTS
    power
)

foreach(ITERATOR_TEST ${ITERATOR_TESTS})
    add_executable(${ITERATOR_TEST} ${ITERATOR_TEST}.cpp)
    target_link_libraries(${ITERATOR_TEST} PRIVATE aware_math GTest::gtest_main)
    gtest_discover_tests(${ITERATOR_TEST})
endforeach()
