#pragma once

#include <memory>

#include "../log/log.hpp"
#include "../memory_provider/interface.hpp"
#include "../memory_resource.hpp"

namespace awr::alloc {

namespace linear {

const size_t DefaultChunkSize = 4096;

}  // namespace linear

template <typename T, concepts::MemoryProvider Provider>
class LinearAllocator {
  public:
    using ValType = T;
    using ValPtr = T*;

  private:
    struct BlockNode {
        MemoryBlock memblock;
        BlockNode* next = nullptr;
    };

  private:
    Provider& provider_;
    BlockNode* head_ = nullptr;
    std::size_t offset_in_current_block_ = 0;

  public:
    explicit LinearAllocator(Provider& p) noexcept : provider_(p) {
    }

    LinearAllocator(const LinearAllocator&) = delete;
    LinearAllocator& operator=(const LinearAllocator&) = delete;

    ~LinearAllocator() {
        release_all();
    }

    template <typename U = T>
    eav::Result<U*, AllocErr> allocate(std::size_t n) noexcept {
        const std::size_t bytes_needed = n * sizeof(U);
        const std::size_t alignment = alignof(U);

        if (!head_ || !head_->memblock.ptr_ ||
            offset_in_current_block_ + bytes_needed > head_->memblock.size_) {

            ALLOC_LOG("Need more memory, requesting new block...");

            const std::size_t requested_size =
                std::max(bytes_needed, linear::DefaultChunkSize) + sizeof(BlockNode) + alignment;

            auto maybe_err = allocate_block(requested_size);
            if (maybe_err.is_err()) {
                return eav::make::Err(maybe_err.unwrap_err());
            }

            offset_in_current_block_ = sizeof(BlockNode);
        }

        void* current_pos =
            static_cast<std::byte*>(head_->memblock.ptr_) + offset_in_current_block_;
        std::size_t space_left = head_->memblock.size_ - offset_in_current_block_;

        void* aligned_ptr = std::align(alignment, bytes_needed, current_pos, space_left);

        if (!aligned_ptr) {
            ALLOC_LOG("Alignment failed!");
            return eav::make::Err(AllocErr::InvalidAlignment);
        }

        offset_in_current_block_ = head_->memblock.size_ - space_left + bytes_needed;

        ALLOC_LOG("Allocated " << bytes_needed << " bytes at " << aligned_ptr);
        return eav::make::Ok(static_cast<U*>(aligned_ptr));
    }

    void deallocate(ValPtr, std::size_t) noexcept {
        // do_nothing
    }

  private:
    MemoryResource allocate_block(const std::size_t requested_size) {
        auto result_resource = provider_.acquire(requested_size);
        if (result_resource.is_err()) return result_resource;

        MemoryBlock new_block = result_resource.unwrap_ok();
        BlockNode* new_head = static_cast<BlockNode*>(new_block.ptr_);
        new_head->next = head_;
        new_head->memblock = new_block;
        head_ = new_head;

        ALLOC_LOG("New block acquired. Size: " << requested_size << " head: " << (void*)head_);
        return result_resource;
    }

    void release_all() noexcept {
        ALLOC_LOG("Releasing ALL blocks:");
        while (head_) {
            ALLOC_LOG("Releasing block...");
            BlockNode* next = head_->next;
            provider_.release(head_->memblock);
            head_ = next;
        }
    }
};

}  // namespace awr::alloc
