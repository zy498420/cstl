#ifndef CVECTOR_H_
#define CVECTOR_H_

#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

#include "macro_util.h"
#include "cstl_config.h"
#include "array.h"

#define VECTOR_ITERATOR ARRAY_ITERATOR     

typedef struct cvector_t
{
    VECTOR_ITERATOR begin;
    size_t size;
    size_t capacity;
    size_t element_size;
    const char* element_type;
}*VECTOR;

#define VECTOR_MINIMUM_CAPCITY (16u)

#define VECTOR_ELEMENT_TYPE(v) \
( \
    CONST_VALUE((v)->element_type, const char*) \
)

#define VECTOR_AT_POINTER(v, n, type) \
( \
    (type*)((v)->begin) + n \
)

#define VECTOR_AT_POINTER_SAFE(v, n, type) \
( \
    ((n) < (v)->size) \
    ? (VECTOR_AT_POINTER((v), (n), type)) \
    : (NULL) \
)

#define VECTOR_AT(v, n, type) \
( \
    *(VECTOR_AT_POINTER((v), (n), type)) \
)

#define VECTOR_BEGIN(v) \
( \
    CONST_VALUE((v)->begin, VECTOR_ITERATOR) \
)

#define VECTOR_END(v) \
( \
    (VECTOR_ITERATOR)(((single_byte*)((v)->begin)) + (v)->size * (v)->element_size) \
)

#define VECTOR_FRONT(v, type) \
( \
    VECTOR_AT((v), (0u), type) \
)

#define VECTOR_BACK(v, type) \
( \
    VECTOR_AT((v), ((v)->size - 1u), type) \
)

#define VECTOR_SIZE(v) \
( \
    CONST_VALUE((v)->size, size_t) \
)

#define VECTOR_CAPACITY(v) \
( \
    CONST_VALUE((v)->capacity, size_t) \
)

#define VECTOR_EMPTY(v) \
( \
    (v)->size == 0u \
)

#define VECTOR_RESERVE(v, n, type) \
do \
{ \
    if (n > (v)->capacity) \
    { \
        while(n > (v)->capacity) \
        { \
            (v)->capacity <<= 1u; \
        } \
    } \
    else \
    { \
        while(n < ((v)->capacity >> 1u)) \
        { \
            (v)->capacity >>= 1u; \
        } \
    } \
    (v)->begin = realloc((v)->begin, (v)->capacity * sizeof(type)); \
} while (0)

#define VECTOR_RESIZE(v, n, type) \
do \
{ \
    VECTOR_RESERVE(v, n, type); \
    (v)->size = n; \
} while (0)

#define VECTOR_INIT(v, type) \
(void) ( \
    (v) = (VECTOR)(malloc(sizeof(*v))), \
    (v)->begin = malloc(VECTOR_MINIMUM_CAPCITY * sizeof(type)), \
    (v)->size = 0u, \
    (v)->capacity = VECTOR_MINIMUM_CAPCITY, \
    (v)->element_size = sizeof(type), \
    (v)->element_type = TO_STRING(type) \
)

#define VECTOR_DESTROY(v) \
(void) ( \
    free((v)->begin), \
    free(v), \
    v = NULL \
)

#define VECTOR_PUSH_BACK(v, element, type) \
do \
{ \
    type TMP_VARIABLE(e) = element; \
    ((v)->size != (v)->capacity) ? \
        (*(VECTOR_AT_POINTER((v), (v)->size, type)) = TMP_VARIABLE(e) ) : \
        ((v)->begin = realloc((v)->begin, ((v)->capacity <<= 1u) * sizeof(type)), *(VECTOR_AT_POINTER((v), (v)->size, type)) = TMP_VARIABLE(e) ); \
    ++((v)->size); \
}while(0)

#define VECTOR_POP_BACK(v) \
(void) ( \
    --((v)->size) \
)

#define VECTOR_FILL(v, value, type) \
do \
{ \
    type* TMP_VARIABLE(1) = VECTOR_AT_POINTER(v, 0u, type); \
    while(TMP_VARIABLE(1) != VECTOR_AT_POINTER(v, (v)->size, type)) \
    { \
       *TMP_VARIABLE(1) = value; \
       ++TMP_VARIABLE(1); \
    } \
} while (0)

#define VECTOR_ASSIGN(v, n, value, type) \
do \
{ \
    VECTOR_RESIZE(v, n, type); \
    VECTOR_FILL(v, value, type); \
} while (0)

#define VECTOR_CLEAR(v) \
(void) ( \
    (v)->size = 0u \
)



#endif
