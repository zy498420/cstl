#ifndef CVECTOR_H_
#define CVECTOR_H_

#include <stdlib.h>
#include <malloc.h>
#include "macro_util.h"

typedef struct cvector_t
{
    void  *_ptr;
    size_t _size;
    size_t _capacity;
    const char* _element_type;
}*VECTOR;


#define VECTOR_ELEMENT_TYPE(v) \
( \
    (v)->_element_type \
)

#define VECTOR_AT_POINTER(v, n, t) \
( \
    (t*)((v)->_ptr) + n \
)

#define VECTOR_AT_POINTER_SAFE(v, n, t) \
( \
    ((n) < (v)->_size) \
    ? (VECTOR_AT_POINTER((v), (n), t)) \
    : (NULL) \
)

#define VECTOR_AT(v, n, t) \
( \
    *(VECTOR_AT_POINTER((v), (n), t)) \
)

#define VECTOR_BEGIN(v, t) \
( \
    VECTOR_AT_POINTER((v), (0u), t) \
)

#define VECTOR_END(v, t) \
( \
    VECTOR_AT_POINTER((v), ((v)->_size), t) \
)

#define VECTOR_FRONT(v, t) \
( \
    VECTOR_AT((v), (0u), t) \
)

#define VECTOR_BACK(v, t) \
( \
    VECTOR_AT((v), ((v)->_size - 1u), t) \
)

#define VECTOR_SIZE(v) \
( \
    (v)->_size \
)

#define VECTOR_EMPTY(v) \
( \
    (v)->_size == 0u \
)

#define VECTOR_FULL(v) \
( \
    (v)->_size == (v)->_capacity \
)

#define VECTOR_MINIMUM_CAPCITY (16u)

#define VECTOR_INIT(v, t) \
(void) ( \
    (v) = (VECTOR)(malloc(sizeof(*v))), \
    (v)->_ptr = malloc(VECTOR_MINIMUM_CAPCITY * sizeof(t)), \
    (v)->_size = 0u, \
    (v)->_capacity = VECTOR_MINIMUM_CAPCITY, \
    (v)->_element_type = TO_STRING(t) \
)

#define VECTOR_DESTROY(v) \
(void) ( \
    free((v)->_ptr), \
    free(v), \
    v = 0 \
)

#define VECTOR_PUSH_BACK(v, e, t) \
( \
    ( \
        (v)->_size != (v)->_capacity ? \
            *(VECTOR_END((v), t)) = e : \
            ((v)->_ptr = realloc((v)->_ptr, ((v)->_capacity <<= 1u) * sizeof(t)), *(VECTOR_END((v), t)) = e) \
    ), \
    ++((v)->_size), \
    VECTOR_BACK(v, t) \
)

#define VECTOR_POP_BACK(v) \
(void) ( \
    --((v)->_size) \
)

#define VECTOR_CLEAR(v) \
(void) ( \
    (v)->_size = 0u \
)

#define VECTOR_RESIZE(v, n, t) \
do \
{ \
    while (n > (v)->_capacity) \
    { \
        (v)->_capacity <<= 1u; \
    } \
    (v)->_ptr = realloc((v)->_ptr, (v)->_capacity * sizeof(t)); \
    (v)->_size = n; \
} while (0)

#define VECTOR_FILL(v, e, t) \
do \
{ \
    int n = 0; \
    while (n < (v)->_size) \
    { \
        VECTOR_AT(v, n, t) = e; \
        ++n; \
    } \
} while (0)

#endif
