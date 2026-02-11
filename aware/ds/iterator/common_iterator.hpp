#pragma once

#include <concepts>
#include <cstddef>

#include <aware/ds/iterator/cursor.hpp>
#include <aware/ds/iterator/tag.hpp>
#include <aware/meta/conditional.hpp>

namespace awr::iter {

template <typename ValT, trait::IterCursor CursorT, bool is_const, trait::IterTag Tag>
class CommonIterator {
  public:  // nested types:
    using ValType = ValT;
    using ValPtr = meta::Conditional<is_const, const ValT*, ValT*>::type;
    using ValRef = meta::Conditional<is_const, const ValT&, ValT&>::type;

    using Category = Tag;
    using DiffType = std::ptrdiff_t;

  private:  // data members:
    CursorT cursor_;

  public:  // member functions:
    CommonIterator() {}

    explicit CommonIterator(const CursorT cursor) : cursor_(cursor) {}

    CommonIterator(const CommonIterator& oth) = default;
    CommonIterator& operator=(const CommonIterator& oth) = default;
    CommonIterator(const CommonIterator&& oth) = default;
    CommonIterator& operator=(const CommonIterator&& oth) = default;

    template <bool oth_const> requires(is_const && !oth_const && std::copy_constructible<CursorT>)
    CommonIterator(const CommonIterator<ValT, CursorT, oth_const, Tag>& oth) : cursor_(oth.cursor_) {}

    ValRef operator*() const {
        return cursor_.dereference();
    }

    ValPtr operator->() const {
        return &(cursor_.dereference());
    }

    CommonIterator& operator++() {
        cursor_.increment();
        return *this;
    }

    CommonIterator operator++(int) {
        CommonIterator tmp = *this;
        cursor_.increment();
        return tmp;
    }

    CommonIterator& operator--() requires(std::derived_from<Tag, tag::BidirectionalIterator>)
    {
        cursor_.decrement();
        return *this;
    }

    CommonIterator operator--(int) requires(std::derived_from<Tag, tag::BidirectionalIterator>)
    {
        CommonIterator tmp = *this;
        cursor_.decrement();
        return tmp;
    }

    CommonIterator operator+(DiffType n) const requires(std::derived_from<Tag, tag::RandomAccessIterator>)
    {
        auto next_cursor = cursor_;
        next_cursor.advance(n);
        return CommonIterator(next_cursor);
    }

    CommonIterator& operator+=(DiffType n) requires(std::derived_from<Tag, tag::RandomAccessIterator>);
    CommonIterator& operator-=(DiffType n) requires(std::derived_from<Tag, tag::RandomAccessIterator>);

    DiffType operator-(const CommonIterator& other) const requires(std::derived_from<Tag, tag::RandomAccessIterator>)
    {
        return cursor_.distance_to(other.cursor_);
    }

    bool operator==(const CommonIterator& oth) const {
        return cursor_.is_equal(oth.cursor_);
    }

    template <bool is_oth_const>
    auto operator<=>(const CommonIterator<ValT, CursorT, is_oth_const, Tag>& oth) const
        requires(std::derived_from<Tag, tag::RandomAccessIterator>)
    {
        return cursor_.compare(oth.cursor_);
    }

  public:  // friendship declaration:
    friend class CommonIterator<ValT, CursorT, !is_const, Tag>;
};

}  // namespace awr::iter
