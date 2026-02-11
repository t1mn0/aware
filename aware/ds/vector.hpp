#pragma once

#include <cstddef>  // std::size_t
#include <memory>   // std::allocator

namespace awr::ds {

template <typename T, typename Allocator = std::allocator<T>>
class Vector {
  private:  // data members:
    T* array_ = nullptr;
    std::size_t size_ = 0;
    std::size_t cap_ = 0;
    Allocator alloc_;

  public:  // nested types:
    using ValType = T;
    using ValRef = T&;
    using ConstValRef = const T&;
    using ValPtr = T*;
    using ConstValPtr = const T*;
    using SizeType = std::size_t;

    // using Iterator = ;
    // using IterDiffType = std::size_t;
};

};  // namespace awr::ds
