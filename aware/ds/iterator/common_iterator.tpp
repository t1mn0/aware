/**
 * @file common_iterator.tpp
 * @brief Implementation details for CommonIterator class template.
 */

#pragma once

#include "common_iterator.hpp"

namespace awr::iter {

template <typename ValT, trait::IterCursor CursorT, bool is_const, trait::IterTag Tag>
auto CommonIterator<ValT, CursorT, is_const, Tag>::operator*() const -> ValRef {
    return cursor_.dereference();
}

template <typename ValT, trait::IterCursor CursorT, bool is_const, trait::IterTag Tag>
auto CommonIterator<ValT, CursorT, is_const, Tag>::operator->() const -> ValPtr {
    return &(cursor_.dereference());
}

template <typename ValT, trait::IterCursor CursorT, bool is_const, trait::IterTag Tag>
CommonIterator<ValT, CursorT, is_const, Tag>&
CommonIterator<ValT, CursorT, is_const, Tag>::operator++() {
    cursor_.increment();
    return *this;
}

template <typename ValT, trait::IterCursor CursorT, bool is_const, trait::IterTag Tag>
CommonIterator<ValT, CursorT, is_const, Tag>
CommonIterator<ValT, CursorT, is_const, Tag>::operator++(int) {
    CommonIterator tmp = *this;
    cursor_.increment();
    return tmp;
}

template <typename ValT, trait::IterCursor CursorT, bool is_const, trait::IterTag Tag>
CommonIterator<ValT, CursorT, is_const, Tag>&
CommonIterator<ValT, CursorT, is_const, Tag>::operator--()
    requires(std::derived_from<Tag, tag::BidirectionalIterator>)
{
    cursor_.decrement();
    return *this;
}

template <typename ValT, trait::IterCursor CursorT, bool is_const, trait::IterTag Tag>
CommonIterator<ValT, CursorT, is_const, Tag>
CommonIterator<ValT, CursorT, is_const, Tag>::operator--(int)
    requires(std::derived_from<Tag, tag::BidirectionalIterator>)
{
    CommonIterator tmp = *this;
    cursor_.decrement();
    return tmp;
}

template <typename ValT, trait::IterCursor CursorT, bool is_const, trait::IterTag Tag>
CommonIterator<ValT, CursorT, is_const, Tag>
CommonIterator<ValT, CursorT, is_const, Tag>::operator+(DiffType n) const
    requires(std::derived_from<Tag, tag::RandomAccessIterator>)
{
    auto next_cursor = cursor_;
    next_cursor.advance(n);
    return CommonIterator(next_cursor);
}

template <typename ValT, trait::IterCursor CursorT, bool is_const, trait::IterTag Tag>
CommonIterator<ValT, CursorT, is_const, Tag>&
CommonIterator<ValT, CursorT, is_const, Tag>::operator+=(DiffType n)
    requires(std::derived_from<Tag, tag::RandomAccessIterator>)
{
    cursor_.advance(n);
    return *this;
}

template <typename ValT, trait::IterCursor CursorT, bool is_const, trait::IterTag Tag>
CommonIterator<ValT, CursorT, is_const, Tag>&
CommonIterator<ValT, CursorT, is_const, Tag>::operator-=(DiffType n)
    requires(std::derived_from<Tag, tag::RandomAccessIterator>)
{
    cursor_.advance(-n);
    return *this;
}

template <typename ValT, trait::IterCursor CursorT, bool is_const, trait::IterTag Tag>
auto CommonIterator<ValT, CursorT, is_const, Tag>::operator-(const CommonIterator& oth) const
    -> DiffType requires(std::derived_from<Tag, tag::RandomAccessIterator>)
{
    return cursor_.distance_to(oth.cursor_);
}

template <typename ValT, trait::IterCursor CursorT, bool is_const, trait::IterTag Tag>
bool CommonIterator<ValT, CursorT, is_const, Tag>::operator==(const CommonIterator& oth) const {
    return cursor_.is_equal(oth.cursor_);
}

template <typename ValT, trait::IterCursor CursorT, bool is_const, trait::IterTag Tag>
template <bool is_oth_const> auto CommonIterator<ValT, CursorT, is_const, Tag>::operator<=>(
    const CommonIterator<ValT, CursorT, is_oth_const, Tag>& oth) const
    requires(std::derived_from<Tag, tag::RandomAccessIterator>)
{
    return cursor_.compare(oth.cursor_);
}

}  // namespace awr::iter
