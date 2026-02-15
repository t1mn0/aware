#pragma once

#include <cstddef>  // std::size_t
#include <memory>   // std::allocator

#include <eav/Option.hpp>

#include <aware/ds/iterator/common_iterator.hpp>
#include <aware/ds/iterator/tag.hpp>
#include <aware/ds/vector/cursor.hpp>

namespace awr::ds {

template <typename T, typename Allocator = std::allocator<T>>
class Vector {
  private:  // data members:
    T* array_ = nullptr;
    std::size_t size_ = 0;
    std::size_t cap_ = 0;
    [[no_unique_address]] Allocator alloc_;

  public:  // nested types:
    using ValType = T;
    using ValTRef = T&;
    using ConstValTRef = const T&;
    using ValTPtr = T*;
    using ConstValTPtr = const T*;
    using SizeType = std::size_t;

    using Iterator =
        iter::CommonIterator<T, vec::detail::VectorCursor<T>, false, iter::tag::ContiguousIterator>;
    using ConstIterator =
        iter::CommonIterator<T, vec::detail::VectorCursor<T>, true, iter::tag::ContiguousIterator>;
    using IterDiffType = std::ptrdiff_t;

    using AllocatorType = Allocator;

  public:  // member functions:
    /* --- Lifecycle --- */
    Vector() noexcept(noexcept(Allocator())) = default;

    explicit Vector(SizeType size, const Allocator& alloc = Allocator{});
    explicit Vector(SizeType size, ConstValTRef init_by = {}, const Allocator& alloc = Allocator{});

    Vector(const Vector& oth) requires std::copy_constructible<T>;
    Vector& operator=(const Vector& oth) requires std::copy_constructible<T>;

    Vector(Vector&& oth) noexcept(std::is_nothrow_move_assignable_v<T>);
    Vector& operator=(Vector&& oth) noexcept(std::is_nothrow_move_assignable_v<T>);

    Vector(std::initializer_list<ValType> lst, const Allocator& alloc = Allocator{});

    ~Vector();

    /* --- Accessors (almost all inline) --- */
    SizeType size() const noexcept {
        return size_;
    }

    SizeType capacity() const noexcept {
        return cap_;
    }

    bool empty() const noexcept {
        return size_ == 0;
    }

    ValTRef operator[](SizeType index) noexcept {
        return array_[index];
    }

    ConstValTRef operator[](SizeType index) const noexcept {
        return array_[index];
    }

    ValTRef front() noexcept {
        return array_[0];
    }

    ConstValTRef front() const noexcept {
        return array_[0];
    }

    ValTRef back() noexcept {
        return array_[size_ - 1];
    }

    ConstValTRef back() const noexcept {
        return array_[size_ - 1];
    }

    eav::Option<ConstValTRef> try_at(SizeType index) const noexcept;
    eav::Option<ValTRef> try_at(SizeType index) noexcept;

    /* Modifiers */
    Vector& reserve(SizeType new_cap);  // increase capacity
    Vector& shrink(SizeType new_cap);   // reduce capacity
    Vector& shrink();                   // = shrink_to_fit
    Vector& resize(SizeType new_sz, const T& init_by = T{}) requires std::copy_constructible<T>;
    Vector& clear() noexcept;

    Vector& push_back(ConstValTRef val) requires std::copy_constructible<T>;
    Vector& push_back(ValType&& val) requires std::move_constructible<T>;
    Vector& pop_back() noexcept;

    template <typename... Args>
    requires std::constructible_from<T, Args...>
    Vector& emplace_back(Args&&... args);

    /* Iterators */
    Iterator begin() noexcept;
    ConstIterator begin() const noexcept;
    ConstIterator cbegin() const noexcept;
    Iterator end() noexcept;
    ConstIterator end() const noexcept;
    ConstIterator cend() const noexcept;
    // [TODO]: awr::iter::reverse<Iterator> rbegin() noexcept;
    // [TODO]: awr::iter::reverse<Iterator> rend() noexcept;
};

};  // namespace awr::ds
