////////////////////////////////////////////////////////////////////////////////
/// Copyright 2025 Daniel S. Buckstein
/// 
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
/// 
///     http://www.apache.org/licenses/LICENSE-2.0
/// 
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
////////////////////////////////////////////////////////////////////////////////

/*
* cat_memory.c
* Memory management implementation.
*/

#include "cat/utility/cat_memory.h"
#include "cat/cat_platform.inl"

#include <assert.h>
#include <string.h>


cat_implementation_begin;


#ifdef CAT_DEBUG
typedef struct cat_malloc_metadata_s
{
#ifdef _WIN32
    //****TO-DO-MEMORY: fill in this structure.
    uint32_t test[7];
    uint32_t reserved;
#else // #ifdef _WIN32
    uint32_t reserved;
#endif // #else // #ifdef _WIN32
} cat_malloc_metadata_t;
#endif // #ifdef CAT_DEBUG

typedef struct Heap
{
    void* data;
    int size;
    HeapHeader* first;
    HeapHeader* last;
} Heap;

static Heap my_heap;

typedef struct HeapHeader
{
    int size;
    HeapHeader* prev;
    HeapHeader* next;
    int location;
} HeapHeader;

cat_impl void* cat_memset(void* const p_block, uint8_t const value, size_t const set_size)
{
    assert_or_bail(p_block) NULL;
    assert_or_bail(set_size) NULL;
    return memset(p_block, value, set_size);
}

cat_impl void* cat_memclr(void* const p_block, size_t const clr_size)
{
    return cat_memset(p_block, 0xFF, clr_size);
}

cat_impl void* cat_memcpy(void* const p_block_dst, void const* const p_block_src, size_t const cpy_size)
{
    assert_or_bail(p_block_dst) NULL;
    assert_or_bail(p_block_src) NULL;
    assert_or_bail(cpy_size) NULL;
    return memcpy(p_block_dst, p_block_src, cpy_size);
}

cat_impl bool cat_memcmp(void const* const p_block_lh, void const* const p_block_rh, size_t const cmp_size)
{
    assert_or_bail(p_block_lh) false;
    assert_or_bail(p_block_rh) false;
    assert_or_bail(cmp_size) false;
    return (memcmp(p_block_lh, p_block_rh, cmp_size) == 0);
}

cat_impl void* cat_malloc(size_t const block_size)
{
#ifdef CAT_DEBUG
    cat_malloc_metadata_t* p_meta = NULL;
#endif // #ifdef CAT_DEBUG
    void* p_block = NULL;
    assert_or_bail(block_size) NULL;
    p_block = malloc(block_size);
#ifdef CAT_DEBUG
    unused(p_meta);
#endif // #ifdef CAT_DEBUG
    return p_block;
}

cat_impl void* cat_calloc(size_t const element_count, size_t const element_size)
{
#ifdef CAT_DEBUG
    cat_malloc_metadata_t* p_meta = NULL;
#endif // #ifdef CAT_DEBUG
    void* p_block = NULL;
    assert_or_bail(element_count) NULL;
    assert_or_bail(element_size) NULL;
    p_block = calloc(element_count, element_size);
#ifdef CAT_DEBUG
    unused(p_meta);
#endif // #ifdef CAT_DEBUG
    return p_block;
}

cat_impl void* cat_realloc(void* const p_block, size_t const block_size)
{
#ifdef CAT_DEBUG
    cat_malloc_metadata_t* p_meta = NULL;
#endif // #ifdef CAT_DEBUG
    void* p_block_new = NULL;
    assert_or_bail(p_block) NULL;
    assert_or_bail(block_size) NULL;
    p_block_new = realloc(p_block, block_size);
#ifdef CAT_DEBUG
    unused(p_meta);
#endif // #ifdef CAT_DEBUG
    return p_block_new;
}

cat_impl void cat_free(void* const p_block)
{
#ifdef CAT_DEBUG
    cat_malloc_metadata_t* p_meta = NULL;
#endif // #ifdef CAT_DEBUG
    assert_or_bail(p_block);
#ifdef CAT_DEBUG
    unused(p_meta);
#endif // #ifdef CAT_DEBUG
    cat_free(p_block);
}

cat_impl bool cat_memory_pool_create(size_t const pool_size)
{
    assert_or_bail(pool_size) false;
    
    //****TO-DO-MEMORY: allocate and initialize pool.
    
    if (my_heap.data == NULL)
        cat_memory_pool_destroy();
    my_heap.data = cat_malloc(pool_size);
    my_heap.size = pool_size;
    my_heap.first = NULL;
    my_heap.last = NULL;
    return true;
    return false;
}

cat_impl bool cat_memory_pool_destroy(void)
{
    //****TO-DO-MEMORY: safely deallocate pool allocated above.
    for (HeapHeader* iter = my_heap.first; iter != NULL; )//not sure if this is needed
    {
        HeapHeader* temp = iter;
        iter = iter->next;
        temp->next = NULL;
        temp->prev = NULL;
    }

    cat_free(my_heap.data);
    my_heap.first = NULL;
    my_heap.last = NULL;
    my_heap.size = 0;

    return false;
}

cat_impl void* cat_memory_alloc(size_t const block_size)
{
    assert_or_bail(block_size) NULL;
    
    if (my_heap.last == NULL)
    {
        if (sizeof(HeapHeader) + block_size > my_heap.size)//not enough space to accomodate so you return
            return NULL;

        void* loc = my_heap.data;
        //loc = cat_malloc(sizeof(HeapHeader) + block_size);
        ((HeapHeader*)(loc))->prev = NULL;
        ((HeapHeader*)(loc))->next = NULL;
        ((HeapHeader*)(loc))->location = loc;
        ((HeapHeader*)(loc))->size = block_size;

        return loc;
    }

    void* loc = my_heap.last + sizeof(HeapHeader) + ((HeapHeader*)(my_heap.last))->size;
    
    if (loc > &(my_heap.data) + my_heap.size)
    {
        //not enough size to accomodate for now we just return, but soon will make function to squish the fuckers
        return NULL;
    }

    //loc = cat_malloc(sizeof(HeapHeader) + block_size);
    ((HeapHeader*)loc)->prev = my_heap.last;
    ((HeapHeader*)loc)->next = NULL;
    ((HeapHeader*)loc)->location = loc;
    ((HeapHeader*)loc)->size = block_size;

    my_heap.last = loc;
    my_heap.size += sizeof(HeapHeader) + block_size;

    //****TO-DO-MEMORY: reserve block in managed pool.
    //check where there is free memory and if there is adequete space fill it with this. 

    return loc;
}

cat_impl bool cat_memory_dealloc(void* const p_block)
{
    assert_or_bail(p_block) false;
    void* loc = p_block;
    
    ((HeapHeader*)loc)->prev->next = ((HeapHeader*)loc)->next;
    ((HeapHeader*)loc)->next->prev = ((HeapHeader*)loc)->prev;
    
    if (my_heap.first == loc)
        my_heap.first = ((HeapHeader*)loc)->next;
    if (my_heap.last == loc)
        my_heap.last = ((HeapHeader*)loc)->prev;
    
    ((HeapHeader*)loc)->prev = NULL;
    ((HeapHeader*)loc)->next = NULL;

    //****TO-DO-MEMORY: safely release block reserved above.
    //remove the thing and fill where it was with the things after it in the linked list

    return false;
}

cat_impl void resize_heap()
{
    int moveSize = 0;
    void* loc = my_heap.last;
    
    while (((HeapHeader*)loc)->prev != NULL)
    {
        moveSize += sizeof(HeapHeader) + ((HeapHeader*)loc)->size;
        void* dest = ((HeapHeader*)loc)->prev + sizeof(HeapHeader) + ((HeapHeader*)loc)->size;
        cat_memcpy(dest, loc, moveSize);
        ((HeapHeader*)loc)->prev->next = dest;
        loc = ((HeapHeader*)loc)->prev;
    }

    moveSize += sizeof(HeapHeader) + ((HeapHeader*)loc)->size;
    void* dest = my_heap.data;
    
    cat_memcpy(dest, loc, moveSize);
    my_heap.first = my_heap.data;
    my_heap.last = (my_heap.first + moveSize);
}


#include "cat/utility/cat_time.h"
#include "cat/utility/cat_console.h"


cat_noinl void cat_memory_test(void)
{
    bool result = false;
    void* block_lh = cat_malloc(1024);
    void* block_rh = cat_malloc(2048);

    if (block_lh && block_rh)
    {
        cat_console_clear();
        cat_memset(block_lh, 0xFF, 1024);
        cat_memclr(block_rh, 2048);
        result = cat_memcmp(block_lh, block_rh, 2048);
        printf("\nMemory: \n    Blocks are equal: %"PRIi32, (int32_t)result);
        cat_memcpy(block_lh, block_rh, 1024);
        result = cat_memcmp(block_lh, block_rh, 1024);
        printf("\nMemory: \n    Blocks are equal: %"PRIi32, (int32_t)result);
        cat_platform_sleep(cat_platform_time_rate());
    }

    cat_free(block_lh);
    block_lh = NULL;
    cat_free(block_rh);
    block_rh = NULL;

    if(!cat_memory_pool_create(1024)) return;
    
    HeapHeader* intPointer = cat_memory_alloc(sizeof(int));
    *(int*)(intPointer + sizeof(int)) = 5;
    cat_memory_pool_destroy();
}


cat_implementation_end;