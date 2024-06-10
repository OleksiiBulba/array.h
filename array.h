/*
 * MIT License
 *
 * Copyright (c) 2024 Alexey Kutepov <reximkut@gmail.com>
 * Copyright (c) 2024 Oleksii Bulba <oleksii.bulba@gmail.com>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef ARRAY_H_
#define ARRAY_H_

#include <stdbool.h>

#ifndef ARRAY_ASSERT
#include <assert.h>
#define ARRAY_ASSERT(cond, msg) assert((cond) && msg "\n")
#endif // ARRAY_ASSERT

#ifndef ARRAY_MALLOC
#include <stdlib.h>
#define ARRAY_MALLOC malloc
#endif

#ifndef ARRAY_REALLOC
#include <stdlib.h>
#define ARRAY_REALLOC realloc
#endif // ARRAY_REALLOC

#ifndef ARRAY_FREE
#include <stdlib.h>
#define ARRAY_FREE free
#endif // ARRAY_FREE

#ifndef ARRAY_STRCOPY
#include <string.h>
#define ARRAY_STRCOPY strdup
#endif

#ifndef ARRAY_MEMMMOVE
#include <string.h>
#define ARRAY_MEMMMOVE memmove
#endif

#ifdef ARRAY_DEBUG
#define ARRAY_LOG_DEBUG(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define ARRAY_LOG_DEBUG(...)
#endif

#define ARRAY_FOREACH(type_var, array)    \
    for (size_t _i = 0, _size = (array)->count; _i < _size; ++_i) {  \
        type_var = (array)->items[_i];
#define ARRAY_PTR_FOREACH(type_var, array) \
    for (size_t _i = 0, _size = (array)->count; _i < _size; ++_i) {  \
        type_var = (array)->items[_i].item;
#define ARRAY_FOREACH_END }

#ifdef __cplusplus
extern "C" {
#endif

#define ARRAY_LEN(array) ((array)->count)

#define ARRAY_GET(array, index)    \
    (ARRAY_ASSERT(index >= 0 && index < (array)->count, "Index is out of bounds in array."), (array)->items[index])
#define ARRAY_GET_REF(array, index) \
    (ARRAY_ASSERT(index >= 0 && index < (array)->count, "Index is out of bounds in array."), &(array)->items[index])
#define ARRAY_PTR_GET(array, index) \
    (ARRAY_ASSERT(index >= 0 && index < (array)->count, "Index is out of bounds in array."), (array)->items[index].item)
#define ARRAY_PTR_GET_REF(array, index) \
    (ARRAY_ASSERT(index >= 0 && index < (array)->count, "Index is out of bounds in array."), &((array)->items[index].item))

#define ARRAY(item_type) array_##item_type
#define ARRAY_PTR(item_type) array_array_##item_type
    
#define ARRAY_DEFINE(item_type)         \
    typedef struct ARRAY(item_type) {   \
        item_type* items;               \
        size_t count;                   \
        size_t capacity;                \
    } ARRAY(item_type)

#define ARRAY_PTR_DEFINE(item_type)         \
    typedef struct {                        \
        item_type* item;                    \
        bool should_free;                   \
    } array_ptr_item_##item_type;           \
    typedef struct ARRAY_PTR(item_type) {   \
        array_ptr_item_##item_type* items;  \
        size_t count;                       \
        size_t capacity;                    \
    } ARRAY_PTR(item_type)

#define ARRAY_INIT_CAP 8

#define array_append(array, _item)                                                                          \
    do {                                                                                                    \
        if ((array)->count + 1 >= (array)->capacity) {                                                      \
            (array)->capacity = (array)->capacity == 0 ? ARRAY_INIT_CAP : (array)->capacity * 2;            \
            (array)->items = ARRAY_REALLOC((array)->items, (array)->capacity * sizeof(*(array)->items));    \
            ARRAY_ASSERT((array)->items != NULL, "Cannot reallocate memory for dynamic array");             \
        }                                                                                                   \
        (array)->items[(array)->count++] = (_item);                                                         \
    } while (0)

#define array_ptr_append(array, item)       array_ptr_append_internal((array), (item), true)
#define array_ptr_append_ptr(array, item)   array_ptr_append_internal((array), (item), false)
#define array_ptr_append_internal(array, _item, _should_free)                                               \
    do {                                                                                                    \
        if ((array)->count + 1 >= (array)->capacity) {                                                      \
            (array)->capacity = (array)->capacity == 0 ? ARRAY_INIT_CAP : (array)->capacity * 2;            \
            (array)->items = ARRAY_REALLOC((array)->items, (array)->capacity * sizeof(*(array)->items));    \
            ARRAY_ASSERT((array)->items != NULL, "Cannot reallocate memory for dynamic array");             \
        }                                                                                                   \
        (array)->items[(array)->count].item = (_item);                                                      \
        (array)->items[(array)->count++].should_free = _should_free;                                        \
    } while (0)

#define array_unset(array, index)                                                                           \
    do {                                                                                                    \
        ARRAY_ASSERT(index >= 0 && index < (array)->count, "Index is out of range for array_unset.");       \
        if (index < (array)->count - 1) {                                                                   \
            memmove(&(array)->items[index], &(array)->items[index + 1],                                     \
                    ((array)->count - index - 1) * sizeof(*(array)->items));                                \
        }                                                                                                   \
        (array)->count--;                                                                                   \
    } while (0)

#define array_ptr_unset(array, index)                                                                       \
    do {                                                                                                    \
        ARRAY_ASSERT(index >= 0 && index < (array)->count, "Index is out of range for array_unset.");       \
        if (index < (array)->count - 1) {                                                                   \
            memmove(&(array)->items[index], &(array)->items[index + 1],                                     \
                    ((array)->count - index - 1) * sizeof(*(array)->items));                                \
        }                                                                                                   \
        (array)->count--;                                                                                   \
    } while (0)

#define array_compact(array)                                                                                \
    do {                                                                                                    \
        if ((array)->capacity > (array)->count * 2) {                                                       \
            if ((array)->count > 0) {                                                                       \
                while ((array)->count * 2 < (array)->capacity) { (array)->capacity /= 2; }                  \
                (array)->items = ARRAY_REALLOC((array)->items, (array)->count * sizeof(*(array)->items));   \
                ARRAY_ASSERT((array)->items != NULL, "Failed to reallocate memory during compaction.");     \
            } else {                                                                                        \
                ARRAY_FREE((array)->items);                                                                 \
                (array)->items = NULL;                                                                      \
            }                                                                                               \
            (array)->capacity = (array)->count;                                                             \
        }                                                                                                   \
    } while (0);

#define array_compact_extreme(array)                                                                        \
    do {                                                                                                    \
        if ((array)->capacity > (array)->count) {                                                           \
            if ((array)->count > 0) {                                                                       \
                (array)->items = ARRAY_REALLOC((array)->items, (array)->count * sizeof(*(array)->items));   \
                ARRAY_ASSERT((array)->items != NULL, "Failed to reallocate memory during compaction.");     \
            } else {                                                                                        \
                ARRAY_FREE((array)->items);                                                                 \
                (array)->items = NULL;                                                                      \
            }                                                                                               \
            (array)->capacity = (array)->count;                                                             \
        }                                                                                                   \
    } while (0)

#define array_free(array)                   \
    do {                                    \
        if ((array)->items != NULL) {       \
            ARRAY_FREE((array)->items);     \
            (array)->items = NULL;          \
        }                                   \
        (array)->count = 0;                 \
        (array)->capacity = 0;              \
        ARRAY_FREE(array);                  \
    } while (0)

#define array_ptr_free(array)                                   \
    do {                                                        \
        if ((array)->items != NULL) {                           \
            for (size_t i = 0; i < (array)->count; i++) {       \
                if ((array)->items[i].should_free) {            \
                    ARRAY_FREE((array)->items[i].item);         \
                }                                               \
            }                                                   \
            ARRAY_FREE((array)->items);                         \
            (array)->items = NULL;                              \
        }                                                       \
        (array)->count = 0;                                     \
        (array)->capacity = 0;                                  \
        ARRAY_FREE(array);                                      \
    } while (0)

#define array_new(array_type) array_new_with_cap(array_type, 0)

#define array_new_with_cap(array_type, initial_capacity)  ({                                \
    array_type *arr = ARRAY_MALLOC(sizeof(array_type));                                     \
    ARRAY_ASSERT(arr != NULL, "Failed to allocate memory for array");                       \
    arr->items = NULL;                                                                      \
    arr->count = 0;                                                                         \
    arr->capacity = 0;                                                                      \
    if (initial_capacity > 0) {                                                             \
        arr->items = ARRAY_MALLOC(initial_capacity * sizeof(*(arr->items)));                \
        ARRAY_ASSERT(arr->items != NULL, "Failed to allocate memory for array items");      \
        arr->capacity = initial_capacity;                                                   \
    }                                                                                       \
    arr;                                                                                    \
})

#define array_new_with_items(array_type, items_array, num_items) ({     \
    array_type *arr = array_new(array_type, num_items);                 \
    for (size_t i = 0; i < num_items; i++) {                            \
        array_append(arr, items_array[i]);                              \
    }                                                                   \
    arr;                                                                \
})

#define array_print(array, array_item_printer)                  \
    do {                                                        \
        printf(                                                 \
            "Array at %p -- count: %zu, capacity: %zu\n",       \
            (array),                                            \
            (array)->count,                                     \
            (array)->capacity                                   \
        );                                                      \
        for (size_t i = 0; i < (array)->count; i++) {           \
             array_item_printer;                                \
        }                                                       \
    } while (0)

#define array_copy(from, to)                                                                    \
    do {                                                                                        \
        if ((to)->capacity < (from)->count) {                                                   \
            (to)->items = ARRAY_REALLOC((to)->items, (from)->capacity * sizeof(*(to)->items));  \
            ARRAY_ASSERT((to)->items != NULL, "Cannot reallocate memory for array copy");       \
            (to)->capacity = (from)->capacity;                                                  \
        }                                                                                       \
        memcpy((to)->items, (from)->items, (from)->count * sizeof(*(from)->items));             \
        (to)->count = (from)->count;                                                            \
    } while (0);

#ifdef __cplusplus
}
#endif

#endif // ARRAY_H_

