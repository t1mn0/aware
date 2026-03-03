#include <gtest/gtest.h>

#define ALLOC_DEBUG

#include <aware/alloc/linear/allocator.hpp>
#include <aware/alloc/memory_provider/malloc_provider.hpp>

TEST(LinearAllocatorTest, SimpleAllocation) {
    awr::alloc::MallocProvider provider;
    awr::alloc::LinearAllocator<int, awr::alloc::MallocProvider> alloc(provider);

    auto res = alloc.allocate(10);
    ASSERT_TRUE(res.is_ok());

    int* data = res.unwrap_ok();
    for (int i = 0; i < 10; ++i) data[i] = i;

    /* 40b = 10*sizeof(int)
     * 4120b = 4096b+sizeof(BlockNode)
     *
     * [ BlockNode (Header) ] [ User Data (int* 40b) ] [      Free Space      ]
     * |_____________________|________________________|_______________________|
     * 0                    24                       64                      4120 (bytes)
     * ^                    ^                        ^
     * head_                result.value()           offset_in_current_block_\
     *
     * head_->next = nullptr;
     */

    for (int i = 0; i < 10; ++i) EXPECT_EQ(data[i], i);
}

TEST(LinearAllocatorTest, BlockChaining) {
    awr::alloc::MallocProvider provider;

    awr::alloc::LinearAllocator<double, awr::alloc::MallocProvider> alloc(provider);

    auto res1 = alloc.allocate(1000);
    auto res2 = alloc.allocate(1000);
    auto res3 = alloc.allocate(1000);
    auto res4 = alloc.allocate(1000);

    EXPECT_TRUE(res1.is_ok());
    EXPECT_TRUE(res2.is_ok());
    EXPECT_TRUE(res3.is_ok());
    EXPECT_TRUE(res4.is_ok());

    EXPECT_NE(res1.unwrap_ok(), res2.unwrap_ok());
    EXPECT_NE(res2.unwrap_ok(), res3.unwrap_ok());
    EXPECT_NE(res1.unwrap_ok(), res3.unwrap_ok());
    EXPECT_NE(res2.unwrap_ok(), res4.unwrap_ok());
    EXPECT_NE(res3.unwrap_ok(), res4.unwrap_ok());
}

TEST(LinearAllocatorTest, AlignmentTest) {
    awr::alloc::MallocProvider provider;
    awr::alloc::LinearAllocator<char, awr::alloc::MallocProvider> alloc(provider);

    /*
     * [ BlockNode ] [ char ] [ GAP / PADDING ] [ double (8b) ] [ Free... ]
     * |___________|________|_________________|________________|_________|
     * 0           24       25                32               40
     * ^           ^                          ^                ^
     * head_       res1                      res2             offset
     */

    auto u = alloc.allocate(1);

    auto res = alloc.allocate<double>(1);
    std::uintptr_t addr = reinterpret_cast<std::uintptr_t>(res.unwrap_ok());

    EXPECT_EQ(addr % alignof(double), 0);
}
