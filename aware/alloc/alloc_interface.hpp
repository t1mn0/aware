#pragma once

#include <concepts>

namespace awr::alloc::concepts {

template <typename Alloc, typename T>
concept Allocator = requires(Alloc a, std::size_t n) {
    typename Alloc::ValType;
    typename Alloc::ValPtr;
    { a.allocate(n) } -> std::same_as<typename Alloc::ValPtr>;
    { a.deallocate(std::declval<typename Alloc::ValPtr>(), n) } -> std::same_as<void>;
};

}  // namespace awr::alloc::concepts
