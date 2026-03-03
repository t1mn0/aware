#pragma once

#include <cstddef>

#include "eav/Result.hpp"

namespace awr::alloc {

enum class AllocErr { OutOfMemory, InvalidAlignment, SizeLimitExceeded, ResourceExhausted };

struct MemoryBlock {
    void* ptr_ = nullptr;
    std::size_t size_ = 0;
};

using MemoryResource = eav::Result<MemoryBlock, AllocErr>;

}  // namespace awr::alloc
