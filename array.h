#ifndef ARRAY_H_
#define ARRAY_H_

#include "iterator.h"

#define ARRAY_ITERATOR ARRAY_ITERATOR     //to help IDE parse

#define ARRAY_ITERATOR_NEXT(x, type) ((x) + 1)

#define ARRAY_ITERATOR_LAST(x, type) ((x) - 1)

#define ARRAY_ITERATOR_NEXT_N(x, n, type) ((x) + n)

#define ARRAY_ITERATOR_DEREF(x, type) (*(x))

typedef struct carray_t
{
    void  *data;
    size_t size;
    const char* element_type;
}*ARRAY;

#define ARRAY_ELEMENT_TYPE(a) \
( \
    (a)->element_type \
)

#define ARRAY_AT_POINTER(a, n, type) \
( \
    (type*)((a)->data) + n \
)

#define ARRAY_AT_POINTER_SAFE(a, n, type) \
( \
    ((n) < (a)->size) \
    ? (ARRAY_AT_POINTER((a), (n), type)) \
    : (NULL) \
)

#define ARRAY_AT(a, n, type) \
( \
    *(ARRAY_AT_POINTER((a), (n), type)) \
)

#define ARRAY_BEGIN(a, type) \
( \
    ARRAY_AT_POINTER((a), (0u), type) \
)

#define ARRAY_END(a, type) \
( \
    ARRAY_AT_POINTER((a), ((a)->size), type) \
)

#define ARRAY_FRONT(a, type) \
( \
    ARRAY_AT((a), (0u), type) \
)

#define ARRAY_BACK(a, type) \
( \
    ARRAY_AT((a), ((a)->size - 1u), type) \
)

#define ARRAY_SIZE(a) \
( \
    (a)->size \
)

#define ARRAY_INIT(a, n, type) \
(void) ( \
    (a) = (ARRAY)(malloc(sizeof(*a))), \
    (a)->data = malloc(n * sizeof(type)), \
    (a)->size = n, \
    (a)->element_type = TO_STRING(type) \
)

#define ARRAY_DESTROY(a) \
(void) ( \
    free((a)->data), \
    free(a), \
    a = NULL \
)

#endif
