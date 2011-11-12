#ifndef CVECTOR_H_
#define CVECTOR_H_

#include <stdlib.h>
#include "macro_util.h"
#include "iterator.h"
#include "array.h"

typedef struct cvector_t
{
    void  *begin;
    size_t size;
    size_t capacity;
    size_t element_size;
    const char* element_type;
}*VECTOR;


#define VECTOR_ITERATOR ARRAY_ITERATOR     

#define VECTOR_ELEMENT_TYPE(v) \
( \
    (v)->element_type \
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
    (v)->begin \
)

#define VECTOR_END(v) \
( \
    (void*)(((char*)((v)->begin)) + (v)->size * (v)->element_size) \
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
    (v)->size \
)

#define VECTOR_CAPACITY(v) \
( \
    (v)->capacity \
)

#define VECTOR_EMPTY(v) \
( \
    (v)->size == 0u \
)

#define VECTOR_FULL(v) \
( \
    (v)->size == (v)->capacity \
)

#define VECTOR_MINIMUM_CAPCITY (16u)

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

#define VECTOR_PUSH_BACK(v, e, type) \
( \
    ( \
        (v)->size != (v)->capacity ? \
            (*(VECTOR_END((v), type)) = e) : \
            ((v)->begin = realloc((v)->begin, ((v)->capacity <<= 1u) * sizeof(type)), *(VECTOR_END((v), type)) = e) \
    ), \
    ++((v)->size), \
    VECTOR_BACK(v, type) \
)

#define VECTOR_POP_BACK(v) \
(void) ( \
    --((v)->size) \
)

#define VECTOR_CLEAR(v) \
(void) ( \
    (v)->size = 0u \
)

#define VECTOR_RESERVE(v, n, type) \
do \
{ \
    while (n > (v)->capacity) \
    { \
        (v)->capacity <<= 1u; \
    } \
    (v)->begin = realloc((v)->begin, (v)->capacity * sizeof(type)); \
} while (0)

#define VECTOR_RESIZE(v, n, type) \
do \
{ \
    VECTOR_RESERVE(v, n, type); \
    (v)->size = n; \
} while (0)

#endif
