#pragma once

#include <concepts>

#include <aware/meta/verify/is_same.hpp>

namespace awr::iter::trait {

template <typename C>
concept DefaultCursor = requires(C cursor, const C const_cursor) {
    cursor.increment();
    const_cursor.dereference();
    { const_cursor.is_equal(cursor) } -> std::convertible_to<bool>;
    { cursor.is_equal(const_cursor) } -> std::convertible_to<bool>;
};

template <typename C>
concept BidirectionalCursor = DefaultCursor<C> && requires(C cursor) {
    cursor.decrement();
};

template <typename C>
concept RandomAccessCursor = BidirectionalCursor<C> && requires(C cursor, const C const_cursor, std::ptrdiff_t n) {
    cursor.advance(n);
    const_cursor.compare(const_cursor);  // <=>
    { const_cursor.distance_to(const_cursor) } -> std::convertible_to<std::ptrdiff_t>;
};

template <typename C>
concept IterCursor = RandomAccessCursor<C> || BidirectionalCursor<C> || DefaultCursor<C>;

}  // namespace awr::iter::trait
