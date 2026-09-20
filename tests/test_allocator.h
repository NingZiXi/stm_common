/**
 * @file    test_allocator.h
 * @brief   独立 ARM 测试的可注入故障分配器
 */
#ifndef TEST_ALLOCATOR_H
#define TEST_ALLOCATOR_H
#include <stddef.h>
#include <stdint.h>

static union { uint64_t align; uint8_t data[256]; } slots[4];
static unsigned occupied[4], live_allocations, allocation_calls, invalid_frees;
static int allocation_failure;

// 分配固定测试槽并清零
void *calloc(size_t count, size_t size)
{
    ++allocation_calls;
    if (allocation_failure || count == 0U || size > 256U / count) { return NULL; }
    for (unsigned i = 0; i < 4U; ++i) {
        if (!occupied[i]) {
            occupied[i] = 1U;
            ++live_allocations;
            for (unsigned j = 0; j < 256U; ++j) { slots[i].data[j] = 0U; }
            return slots[i].data;
        }
    }
    return NULL;
}

// 检查重复释放和非法指针
void free(void *pointer)
{
    if (pointer == NULL) { return; }
    for (unsigned i = 0; i < 4U; ++i) {
        if (pointer == slots[i].data && occupied[i]) {
            occupied[i] = 0U;
            --live_allocations;
            return;
        }
    }
    ++invalid_frees;
}
#endif
