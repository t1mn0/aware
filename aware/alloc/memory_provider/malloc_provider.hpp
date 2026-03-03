#pragma once

#include <cstdlib>

#include "../memory_resource.hpp"

namespace awr::alloc {

struct MallocProvider {
  public:  // member functions:
    MemoryResource acquire(const std::size_t n) noexcept {
        if (void* p = std::malloc(n)) {
            return eav::make::Ok(MemoryBlock{p, n});
        }
        return eav::make::Err(AllocErr::OutOfMemory);
    }

    void release(MemoryBlock block) noexcept {
        if (block.ptr_) {
            std::free(block.ptr_);
        }
    }
};

}  // namespace awr::alloc
