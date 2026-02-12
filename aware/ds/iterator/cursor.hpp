/**
 * @file cursor.hpp
 * @brief Definition of Cursor concepts used by CommonIterator.
 */

#pragma once

#include <concepts>

#include <aware/meta/verification.hpp>

// Cursors are container traversal strategies used in iterators;

namespace awr::iter::trait {

/**
 * @brief Requirements for a cursor supporting forward traversal.
 */
template <typename C>
concept ForwardCursor = requires(C cursor, const C const_cursor) {
    cursor.increment();          // ++it
    const_cursor.dereference();  // *it
    { const_cursor.is_equal(cursor) } -> std::convertible_to<bool>;
    { cursor.is_equal(const_cursor) } -> std::convertible_to<bool>;
};

/**
 * @brief Requirements for a cursor supporting bidirectional traversal.
 */
template <typename C>
concept BidirectionalCursor = ForwardCursor<C> && requires(C cursor) {
    cursor.decrement();  // --it
};

/**
 * @brief Requirements for a cursor supporting random access traversal.
 */
template <typename C>
concept RandomAccessCursor =
    BidirectionalCursor<C> && requires(C cursor, const C const_cursor, std::ptrdiff_t n) {
        cursor.advance(n);                   // it + int
        const_cursor.compare(const_cursor);  // it1 <=> it2
        {
            const_cursor.distance_to(const_cursor)
        } -> std::convertible_to<std::ptrdiff_t>;  // it1 - it2
    };

/**
 * @brief Aggregate concept that matches any valid iterator cursor.
 */
template <typename C>
concept IterCursor = (RandomAccessCursor<C> || BidirectionalCursor<C> || ForwardCursor<C>) &&
                     std::copy_constructible<C>;

}  // namespace awr::iter::trait
