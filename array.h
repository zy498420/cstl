#ifndef ARRAY_H_
#define ARRAY_H_

#include "iterator.h"

#define ARRAY_ITERATOR_NEXT(x, type) ((type*)(x) + 1u)

#define ARRAY_ITERATOR_LAST(x, type) ((type*)(x) - 1u)

#define ARRAY_ITERATOR_NEXT_N(x, n, type) ((type*)(x) + n)

#define ARRAY_ITERATOR_VALUE_REF(x, type) (*((type*)(x)))

typedef struct carray_t
{
    void *begin;
    void *end;
    const char* element_type;
}*ARRAY;

typedef void *ARRAY_ITERATOR;   

#define ARRAY_ELEMENT_TYPE(a) \
( \
    (a)->element_type \
)

#define ARRAY_SIZE(a, type) \
( \
    (type*)((a)->end) -  (type*)((a)->begin) \
)
#define ARRAY_AT_POINTER(a, n, type) \
( \
    (type*)((a)->begin) + n \
)

#define ARRAY_AT_POINTER_SAFE(a, n, type) \
( \
    ((n) < ARRAY_SIZE((a), type)) \
    ? (ARRAY_AT_POINTER((a), (n), type)) \
    : (NULL) \
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

#define ARRAY_FRONT(a, type) \
( \
    ARRAY_AT((a), (0u), type) \
)

#define ARRAY_BACK(a, type) \
( \
    *((type*)(ARRAY_END(a)) - 1u) \
)



#define ARRAY_INIT(a, n, type) \
(void) ( \
    (a) = (ARRAY)(malloc(sizeof(*(a)))), \
    (a)->begin = malloc((n) * sizeof(type)), \
    (a)->end = ARRAY_AT_POINTER((a), (n), type), \
    (a)->element_type = TO_STRING(type) \
)

#define ARRAY_DESTROY(a) \
(void) ( \
    free((a)->begin), \
    free(a), \
    a = NULL \
)

#endif
