#include <gtest/gtest.h>

#include <aware/ds/iterator/common_iterator.hpp>
#include <vector>

// Bidirectional Iterator (Doubly Linked List)

struct Node {
    int val;
    Node* next = nullptr;
    Node* prev = nullptr;

    Node(int val) : val(val) {}
};

template <typename T>
struct ListCursor {
    Node* node;

    ListCursor(Node* n) {
        node = n;
    }

    T& dereference() const { return node->val; }
    void increment() { node = node->next; }
    void decrement() { node = node->prev; }
    bool is_equal(const ListCursor& oth) const { return node == oth.node; }
};

TEST(IteratorPatternsTest, BidirectionalList) {
    Node n1{10}, n2{20}, n3{30};
    n1.next = &n2; n2.prev = &n1;
    n2.next = &n3; n3.prev = &n2;

    using Iter = awr::iter::CommonIterator<int, ListCursor<int>, false,
                                           awr::iter::tag::BidirectionalIterator>;

    Iter it(ListCursor<int>{&n1});

    EXPECT_EQ(*it, 10);
    ++it;
    ++it;
    EXPECT_EQ(*it, 30);
    --it;
    EXPECT_EQ(*it, 20);
}


// Random (but not Contiguous) Access Iterator (Paged/Segmented example (like std::deque))

struct PageCursor {
    std::vector<std::vector<int>>* pages;
    size_t page_size;
    size_t global_idx;

    int& dereference() const { return (*pages)[global_idx / page_size][global_idx % page_size]; }
    void increment() { ++global_idx; }
    void decrement() { --global_idx; }
    void advance(std::ptrdiff_t n) { global_idx += n; }
    bool is_equal(const PageCursor& oth) const { return global_idx == oth.global_idx; }

    std::ptrdiff_t distance_to(const PageCursor& oth) const {
        return static_cast<std::ptrdiff_t>(global_idx) -
               static_cast<std::ptrdiff_t>(oth.global_idx);
    }

    auto compare(const PageCursor& oth) const { return global_idx <=> oth.global_idx; }
};

TEST(IteratorPatternsTest, PagedRandomAccess) {
    std::vector<std::vector<int>> data = {{1, 2}, {3, 4}, {5, 6}};

    using PagedIter = awr::iter::CommonIterator<int, PageCursor, false, awr::iter::tag::RandomAccessIterator>;

    PagedIter it(PageCursor{&data, 2, 0});      // points to 1
    PagedIter it_end(PageCursor{&data, 2, 5});  // points to 6

    EXPECT_EQ(*it, 1);
    it += 3;            // jump across pages: Page 0 -> Page 1
    EXPECT_EQ(*it, 4);  // data[1][1]

    EXPECT_EQ(it_end - it, 2);  // 5 - 3 = 2
    EXPECT_TRUE(it < it_end);
}
