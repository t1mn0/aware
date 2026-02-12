#include <cassert>
#include <iostream>

#include <aware/ds/iterator/common_iterator.hpp>

template <typename T> struct ArrayCursor {
    T* ptr;

    T& dereference() const { return *ptr; }

    void increment() { ++ptr; }

    bool is_equal(const ArrayCursor& oth) const { return ptr == oth.ptr; }

    void decrement() { --ptr; }

    void advance(std::ptrdiff_t n) { ptr += n; }

    std::ptrdiff_t distance_to(const ArrayCursor& oth) const { return ptr - oth.ptr; }

    auto compare(const ArrayCursor& oth) const { return ptr <=> oth.ptr; }
};

struct Node {
    int value;
    Node* next = nullptr;
};

template <typename T> struct ForwardListCursor {
    Node* current;

    T& dereference() const { return current->value; }

    void increment() {
        if (current) current = current->next;
    }

    bool is_equal(const ForwardListCursor& oth) const { return current == oth.current; }
};

int main() {
    {
        int data[] = {10, 20, 30, 40, 50};

        using Iter = awr::iter::CommonIterator<int, ArrayCursor<int>, false,
                                               awr::iter::tag::RandomAccessIterator>;
        using ConstIter = awr::iter::CommonIterator<int, ArrayCursor<int>, true,
                                                    awr::iter::tag::RandomAccessIterator>;

        Iter begin(ArrayCursor<int>{&data[0]});
        Iter end(ArrayCursor<int>{&data[5]});

        for (auto it = begin; it != end; ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        auto it_back = end;
        while (it_back != begin) {
            --it_back;
            std::cout << *it_back << " ";
        }
        std::cout << std::endl;

        Iter middle = begin + 2;
        assert(*middle == 30);
        assert((end - begin) == 5);

        ConstIter c_begin = begin;
        assert(c_begin == begin);
        assert(begin < end);
        assert(end > begin);
        assert(begin <= middle);

        std::cout << "all ArrayIterator asserts passed successfully\n" << std::endl;
    }

    {
        Node n3{30, nullptr};
        Node n2{20, &n3};
        Node n1{10, &n2};

        using ListIter = awr::iter::CommonIterator<int, ForwardListCursor<int>, false,
                                                   awr::iter::tag::ForwardIterator>;

        ListIter begin(ForwardListCursor<int>{&n1});
        ListIter end(ForwardListCursor<int>{nullptr});

        for (auto it = begin; it != end; ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        auto it = begin;
        ++it;
        assert(*it == 20);
        assert(begin != end);

        std::cout << "all ForwardListIterator asserts passed successfully" << std::endl;
    }

    return 0;
}
