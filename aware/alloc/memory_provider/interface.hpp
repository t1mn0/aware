#pragma once

#include <concepts>

#include "../memory_resource.hpp"

namespace awr::alloc::concepts {

template <typename Provider>
concept MemoryProvider = requires(Provider p, std::size_t n, MemoryBlock block) {
    { p.acquire(n) } noexcept -> std::same_as<MemoryResource>;
    { p.release(block) } -> std::same_as<void>;
};

}  // namespace awr::alloc::concepts
