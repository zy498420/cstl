#ifndef ARRAY_H_
#define ARRAY_H_

#include <stdlib.h>
#include <stddef.h>
#include "iterator.h"

typedef struct carray_t
{
    void *begin;
    void *end;
    size_t size;
    const char* element_type;
}*ARRAY;

#define ARRAY_ELEMENT_TYPE(a) \
( \
    (a)->element_type \
)

#define ARRAY_SIZE(a) \
( \
    (a)->size \
)
#define ARRAY_AT_POINTER(a, n, type) \
( \
    (type*)((a)->begin) + n \
)

#define ARRAY_AT(a, n, type) \
( \
    *(ARRAY_AT_POINTER((a), (n), type)) \
)

#define ARRAY_BEGIN(a) \
( \
    (a)->begin \
)

#define ARRAY_END(a) \
( \
    (a)->end \
)

#define ARRAY_RBEGIN(a, type) \
( \
    (type*)((a)->end) - 1 \
)

#define ARRAY_REND(a, type) \
( \
    (type*)((a)->begin) - 1 \
)

#define ARRAY_FRONT(a, type) \
( \
    ARRAY_AT((a), (0u), type) \
)

#define ARRAY_BACK(a, type) \
( \
    ARRAY_AT((a), ((a)->size - 1u), type) \
)

#define ARRAY_INIT(a, n, type) \
(void) ( \
    (a) = (ARRAY)(malloc(sizeof(*(a)))), \
    (a)->begin = malloc((n) * sizeof(type)), \
    (a)->end = ARRAY_AT_POINTER((a), (n), type), \
    (a)->size = n, \
    (a)->element_type = TO_STRING(type) \
)

#define ARRAY_DESTROY(a) \
(void) ( \
    free((a)->begin), \
    free(a), \
    a = NULL \
)

#endif
