/**
 * @file common_iterator.hpp
 * @brief Main header for the generic CommonIterator class.
 */

#pragma once

#include <concepts>
#include <cstddef>

#include <aware/ds/iterator/cursor.hpp>
#include <aware/ds/iterator/tag.hpp>
#include <aware/meta/conditional.hpp>

namespace awr::iter {

/**
 * @class CommonIterator
 * @brief A generic iterator interface that wraps a Cursor and maps its methods to standard iterator
 * operators.
 *
 * CommonIterator serves as a generic interface wrapper that decouples traversal logic from the
 * iterator's operator surface. Instead of implementing complex iterator logic for every container,
 * the `aware` framework uses this class to map a lightweight CursorT (defining 'how to move') to a
 * full set of operators. CommonIterator reduces code duplication when building iterators for
 * various data structures.
 *
 * @tparam ValT The value type of the underlying container.
 * @tparam CursorT The strategy providing core movement and access logic.
 * @tparam is_const Boolean flag to determine if this is a const_iterator.
 * @tparam Tag Capability marker defining the iterator category.
 */

template <typename ValT, trait::IterCursor CursorT, bool is_const, trait::IterTag Tag>
class CommonIterator {
  public:  // nested types:
    using ValType = ValT;
    using ValPtr = typename meta::Conditional<is_const, const ValT*, ValT*>::type;
    using ValRef = typename meta::Conditional<is_const, const ValT&, ValT&>::type;

    using Category = Tag;
    using DiffType = std::ptrdiff_t;

  private:            // data members:
    CursorT cursor_;  ///< The underlying cursor instance.

  public:  // member functions:
    /**
     * @brief Default constructor.
     */
    CommonIterator() = default;

    /**
     * @brief Construct an iterator from a specific cursor position.
     * @param cursor The cursor instance to wrap.
     */
    explicit CommonIterator(const CursorT& cursor) : cursor_(cursor) {
    }

    // Default copy/move constructors and assignment operators
    CommonIterator(const CommonIterator& oth) = default;
    CommonIterator& operator=(const CommonIterator& oth) = default;
    CommonIterator(const CommonIterator&& oth) = default;
    CommonIterator& operator=(const CommonIterator&& oth) = default;

    /**
     * @brief Conversion constructor allowing iterator to const_iterator conversion.
     * @tparam oth_const Constness of the source iterator.
     * @note Enabled only when converting from non-const to const.
     */
    template <bool oth_const>
    requires(is_const && !oth_const)
    CommonIterator(const CommonIterator<ValT, CursorT, oth_const, Tag>& oth)
        : cursor_(oth.cursor_) {
    }

    /**
     * @brief Dereferences the iterator to access the value.
     * @return Reference to the value (const or non-const based on is_const).
     */
    ValRef operator*() const;

    /**
     * @brief Accesses the underlying value via pointer.
     * @return Pointer to the value.
     */
    ValPtr operator->() const;

    /**
     * @brief Pre-increment operator.
     * @return Reference to this iterator after incrementing.
     */
    CommonIterator& operator++();

    /**
     * @brief Post-increment operator.
     * @return A copy of the iterator before incrementing.
     */
    CommonIterator operator++(int);

    /**
     * @brief Pre-decrement operator.
     * @note Available only for Bidirectional or stronger categories.
     */
    CommonIterator& operator--() requires(std::derived_from<Tag, tag::BidirectionalIterator>);

    /**
     * @brief Post-decrement operator.
     * @note Available only for Bidirectional or stronger categories.
     */
    CommonIterator operator--(int) requires(std::derived_from<Tag, tag::BidirectionalIterator>);

    /**
     * @brief Offset addition operator.
     * @note Available only for RandomAccess categories.
     */
    CommonIterator operator+(DiffType n) const
        requires(std::derived_from<Tag, tag::RandomAccessIterator>);

    /**
     * @brief Compound addition assignment.
     * @note Available only for RandomAccess categories.
     */
    CommonIterator& operator+=(DiffType n)
        requires(std::derived_from<Tag, tag::RandomAccessIterator>);

    /**
     * @brief Compound subtraction assignment.
     * @note Available only for RandomAccess categories.
     */
    CommonIterator& operator-=(DiffType n)
        requires(std::derived_from<Tag, tag::RandomAccessIterator>);

    /**
     * @brief Calculates the distance between two iterators.
     * @note Available only for RandomAccess categories.
     */
    DiffType operator-(const CommonIterator& oth) const
        requires(std::derived_from<Tag, tag::RandomAccessIterator>);

    /**
     * @brief Equality comparison operator.
     */
    bool operator==(const CommonIterator& oth) const;

    /**
     * @brief Spaceship comparison operator.
     * @note Available only for RandomAccess categories.
     */
    template <bool is_oth_const>
    auto operator<=>(const CommonIterator<ValT, CursorT, is_oth_const, Tag>& oth) const
        requires(std::derived_from<Tag, tag::RandomAccessIterator>);

  public:  // friendship declaration:
    /**
     * @brief Allows access to private class members between const and non-const versions of the
     * iterator.
     */
    friend class CommonIterator<ValT, CursorT, !is_const, Tag>;
};

}  // namespace awr::iter

#include "common_iterator.tpp"
