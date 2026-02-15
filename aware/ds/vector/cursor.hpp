/**
 * @file cursor.hpp
 * @brief Traversal strategy for contiguous memory containers (Vector).
 */

#pragma once

#include <cstddef>  // std::ptrdiff_t

namespace awr::vec::detail {

/**
 * @struct VectorCursor
 * @brief A cursor implementation for contiguous memory access.
 *
 * Satisfies the RandomAccessCursor concept by wrapping a raw pointer
 * and providing arithmetic operations.
 *
 * @tparam T The type of elements stored in the vector.
 */
template <typename T>
struct VectorCursor {
  public:              // data members:
    T* ptr = nullptr;  ///< Underlying pointer to the element.

  public:  // member functions:
    /**
     * @brief Access the element at the current position.
     * @return Reference to the element.
     */
    T& dereference() const {
        return *ptr;
    }

    /**
     * @brief Move the cursor to the next element.
     */
    void increment() {
        ++ptr;
    }

    /**
     * @brief Move the cursor to the previous element.
     */
    void decrement() {
        --ptr;
    }

    /**
     * @brief Advance the cursor by a given offset.
     * @param n Number of elements to skip (can be negative).
     */
    void advance(std::ptrdiff_t n) {
        ptr += n;
    }

    /**
     * @brief Check if two cursors point to the same location.
     * @param oth Another cursor to compare with.
     * @return true if pointers are equal.
     */
    bool is_equal(const VectorCursor& oth) const {
        return ptr == oth.ptr;
    }

    /**
     * @brief Calculate the distance between this cursor and another.
     * @param oth The reference cursor (usually 'begin').
     * @return Number of elements between cursors.
     */
    std::ptrdiff_t distance_to(const VectorCursor& oth) const {
        return ptr - oth.ptr;
    }

    /**
     * @brief Perform a three-way comparison between cursor positions.
     * @param oth Another cursor to compare with.
     * @return Comparison result (less, equal, or greater).
     */
    auto compare(const VectorCursor& oth) const {
        return ptr <=> oth.ptr;
    }
};

}  // namespace awr::vec::detail
