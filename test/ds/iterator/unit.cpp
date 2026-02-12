#include <gtest/gtest.h>

#include <aware/ds/iterator/common_iterator.hpp>

// --- Cursor for testing ---

template <typename T>
struct TestArrayCursor {
    T* ptr = nullptr;

    T& dereference() const { return *ptr; }
    void increment() { ++ptr; }
    void decrement() { --ptr; }
    void advance(std::ptrdiff_t n) { ptr += n; }
    bool is_equal(const TestArrayCursor& oth) const { return ptr == oth.ptr; }
    std::ptrdiff_t distance_to(const TestArrayCursor& oth) const { return ptr - oth.ptr; }
    auto compare(const TestArrayCursor& oth) const { return ptr <=> oth.ptr; }
};

// --- Test Fixture ---
class CommonIteratorTest : public ::testing::Test {
protected:
    int data[5] = {10, 20, 30, 40, 50};

    using Iter = awr::iter::CommonIterator<int, TestArrayCursor<int>, false, awr::iter::tag::RandomAccessIterator>;
    using ConstIter = awr::iter::CommonIterator<int, TestArrayCursor<int>, true, awr::iter::tag::RandomAccessIterator>;

    Iter begin() { return Iter(TestArrayCursor<int>{&data[0]}); }
    Iter end()   { return Iter(TestArrayCursor<int>{&data[5]}); }
};

TEST_F(CommonIteratorTest, ForwardIteration) {
    auto it = begin();
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(*it, 20);
    it++;
    EXPECT_EQ(*it, 30);
    EXPECT_EQ(*(++it), 40);
}

TEST_F(CommonIteratorTest, BackwardIteration) {
    auto it = end();
    --it;
    EXPECT_EQ(*it, 50);
    it--;
    EXPECT_EQ(*it, 40);
    EXPECT_EQ(*(--it), 30);
}

TEST_F(CommonIteratorTest, RandomAccessArithmetic) {
    auto it = begin();

    EXPECT_EQ(*(it + 3), 40);
    it += 2;
    EXPECT_EQ(*it, 30);

    it -= 1;
    EXPECT_EQ(*it, 20);

    EXPECT_EQ(end() - begin(), 5);
    EXPECT_EQ(begin() - end(), -5);
}

TEST_F(CommonIteratorTest, Comparisons) {
    auto it1 = begin();
    auto it2 = begin() + 2;
    auto it3 = end();

    EXPECT_TRUE(it1 == it1);
    EXPECT_TRUE(it1 != it2);
    EXPECT_TRUE(it1 < it2);
    EXPECT_TRUE(it2 > it1);
    EXPECT_TRUE(it1 <= it2);
    EXPECT_TRUE(it3 >= it2);

    EXPECT_EQ(it1 <= it1, 1);
    EXPECT_EQ(it1 >= it1, 1);
}

TEST_F(CommonIteratorTest, ConstCompatibility) {
    Iter it = begin();
    ConstIter cit = it; // non-const to const

    EXPECT_EQ(*it, *cit);
    EXPECT_TRUE(it == cit);
    EXPECT_TRUE(cit == it);

    EXPECT_FALSE(it != cit);

    cit = end();
    EXPECT_TRUE(it < cit);
    EXPECT_TRUE(cit > it);
}

TEST_F(CommonIteratorTest, ArrowOperator) {
    struct Point { int x, y; };
    Point points[1] = {{1, 2}};

    using PointCursor = TestArrayCursor<Point>;
    using PointIter = awr::iter::CommonIterator<Point, PointCursor, false, awr::iter::tag::ForwardIterator>;

    PointIter it(PointCursor{&points[0]});
    EXPECT_EQ(it->x, 1);
    EXPECT_EQ(it->y, 2);
}
