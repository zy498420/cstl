#ifndef CVECTOR_H_
#define CVECTOR_H_

#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

#include "macro_util.h"
#include "cstl_config.h"
#include "array.h"

typedef struct cvector_t
{
    void* begin;
    void* end;
    size_t size;
    size_t capacity;
    const char* element_type;
}*VECTOR;

#define VECTOR_ITERATOR ARRAY_ITERATOR

#define VECTOR_REVERSE_ITERATOR ARRAY_REVERSE_ITERATOR

typedef VECTOR VECTOR_BACK_INSERT_ITERATOR;

#define VECTOR_BACK_INSERT_ITERATOR_INCREMENT(x, type) ((void)(0))

#define VECTOR_BACK_INSERT_ITERATOR_VALUE_SET(x, value, type) VECTOR_PUSH_BACK(x, value, type)

#define VECTOR_MINIMUM_CAPCITY (16u)

#define VECTOR_ELEMENT_TYPE(_v) \
( \
    ARRAY_ELEMENT_TYPE(_v) \
)

#define VECTOR_AT_POINTER(_v, _n, _type) \
( \
    ARRAY_AT_POINTER(_v, _n, _type) \
)

#define VECTOR_AT(_v, _n, _type) \
( \
    *(VECTOR_AT_POINTER((_v), (_n), _type)) \
)

#define VECTOR_BEGIN(_v) \
( \
    ARRAY_BEGIN(_v) \
)

#define VECTOR_END(_v) \
( \
    ARRAY_END(_v) \
)

#define VECTOR_RBEGIN(_v, type) \
( \
    ARRAY_RBEGIN(_v, type) \
)

#define VECTOR_REND(_v, type) \
( \
    ARRAY_REND(_v, type) \
)

#define VECTOR_FRONT(_v, _type) \
( \
    ARRAY_FRONT(_v, _type) \
)

#define VECTOR_BACK(_v, _type) \
( \
    ARRAY_BACK(_v, _type) \
)

#define VECTOR_SIZE(_v) \
( \
    ARRAY_SIZE(_v) \
)

#define VECTOR_CAPACITY(_v) \
( \
    CONST_VALUE((_v)->capacity, size_t) \
)

#define VECTOR_EMPTY(_v) \
( \
    (_v)->size == 0u \
)

#define VECTOR_RESERVE(_v, _n, _type) \
do \
{ \
    VECTOR const TMP_VARIABLE(v) = (_v); \
    size_t const TMP_VARIABLE(n) = (_n); \
\
    while((TMP_VARIABLE(n)) > (TMP_VARIABLE(v)->capacity)) \
    { \
        (TMP_VARIABLE(v))->capacity <<= 1u; \
    } \
    while(TMP_VARIABLE(n) < ((TMP_VARIABLE(v))->capacity >> 1u)) \
    { \
        (TMP_VARIABLE(v))->capacity >>= 1u; \
    } \
\
    (TMP_VARIABLE(v))->begin = realloc((TMP_VARIABLE(v))->begin, (TMP_VARIABLE(v))->capacity * sizeof(_type)); \
    TMP_VARIABLE(v)->end = VECTOR_AT_POINTER(TMP_VARIABLE(v), (TMP_VARIABLE(v))->size, _type); \
} while (0)

#define VECTOR_RESIZE(_v, _n, _type) \
do \
{ \
    VECTOR const TMP_VARIABLE(v) = (_v); \
    size_t const TMP_VARIABLE(n) = (_n); \
    /*CALL VECTOR_RESERVE(TMP_VARIABLE(v), TMP_VARIABLE(n), _type);*/ \
    while((TMP_VARIABLE(n)) > (TMP_VARIABLE(v)->capacity)) \
    { \
        (TMP_VARIABLE(v))->capacity <<= 1u; \
    } \
    while(TMP_VARIABLE(n) < ((TMP_VARIABLE(v))->capacity >> 1u)) \
    { \
        (TMP_VARIABLE(v))->capacity >>= 1u; \
    } \
\
    (TMP_VARIABLE(v))->begin = realloc((TMP_VARIABLE(v))->begin, (TMP_VARIABLE(v))->capacity * sizeof(_type)); \
    TMP_VARIABLE(v)->end = VECTOR_AT_POINTER(TMP_VARIABLE(v),TMP_VARIABLE(n), _type); \
    TMP_VARIABLE(v)->size = TMP_VARIABLE(n); \
} while (0)

#define VECTOR_INIT(_v, _type) \
(void) ( \
    (_v) = (VECTOR)(malloc(sizeof(*_v))), \
    (_v)->begin = malloc(VECTOR_MINIMUM_CAPCITY * sizeof(_type)), \
    (_v)->end = VECTOR_AT_POINTER((_v), (0u), _type), \
    (_v)->size = 0u, \
    (_v)->capacity = VECTOR_MINIMUM_CAPCITY, \
    (_v)->element_type = TO_STRING(_type) \
)

#define VECTOR_DESTROY(_v) \
(void) ( \
    ARRAY_DESTROY(_v) \
)

#define VECTOR_PUSH_BACK(_v, _e, _type) \
do \
{ \
    VECTOR const TMP_VARIABLE(v) = (_v); \
    _type const TMP_VARIABLE(e) = (_e); \
    if(TMP_VARIABLE(v)->size == TMP_VARIABLE(v)->capacity) \
    {\
        TMP_VARIABLE(v)->begin = realloc(TMP_VARIABLE(v)->begin, (TMP_VARIABLE(v)->capacity <<= 1u) * sizeof(_type)); \
    }\
    *(VECTOR_AT_POINTER(TMP_VARIABLE(v), TMP_VARIABLE(v)->size, _type)) =  TMP_VARIABLE(e); \
    TMP_VARIABLE(v)->end = VECTOR_AT_POINTER(TMP_VARIABLE(v), TMP_VARIABLE(v)->size, _type); \
    ++(TMP_VARIABLE(v)->size); \
}while(0)

#define VECTOR_POP_BACK(_v) \
(void) ( \
    --((_v)->size) \
)

#define VECTOR_FILL(_v, _e, _type) \
do \
{ \
    VECTOR const TMP_VARIABLE(v) = (_v); \
    _type const TMP_VARIABLE(e) = (_e); \
    _type* TMP_VARIABLE(0) = VECTOR_AT_POINTER(TMP_VARIABLE(v), 0u, _type); \
    VECTOR_ITERATOR* const TMP_VARIABLE(1) = VECTOR_END(TMP_VARIABLE(v)); \
    while(TMP_VARIABLE(0) != TMP_VARIABLE(1)) \
    { \
       *TMP_VARIABLE(0) = TMP_VARIABLE(e); \
       ++TMP_VARIABLE(0); \
    } \
} while (0)

#define VECTOR_ASSIGN(_v, _n, _e, _type) \
do \
{ \
    VECTOR const TMP_VARIABLE(v) = (_v); \
    size_t const TMP_VARIABLE(n) = (_n); \
    _type const TMP_VARIABLE(e) = (_e); \
    /*CALL VECTOR_RESIZE(TMP_VARIABLE(v), TMP_VARIABLE(n), _type); */ \
    while((TMP_VARIABLE(n)) > (TMP_VARIABLE(v)->capacity)) \
    { \
        (TMP_VARIABLE(v))->capacity <<= 1u; \
    } \
    while(TMP_VARIABLE(n) < ((TMP_VARIABLE(v))->capacity >> 1u)) \
    { \
        (TMP_VARIABLE(v))->capacity >>= 1u; \
    } \
\
    (TMP_VARIABLE(v))->begin = realloc((TMP_VARIABLE(v))->begin, (TMP_VARIABLE(v))->capacity * sizeof(_type)); \
    TMP_VARIABLE(v)->end = VECTOR_AT_POINTER(TMP_VARIABLE(v),TMP_VARIABLE(n), _type); \
    TMP_VARIABLE(v)->size = TMP_VARIABLE(n); \
    /*CALL VECTOR_FILL(TMP_VARIABLE(v), TMP_VARIABLE(e), _type);*/ \
    do \
    { \
        _type *TMP_VARIABLE(0) = VECTOR_AT_POINTER(TMP_VARIABLE(v), 0u, _type); \
        while(TMP_VARIABLE(0) != VECTOR_END(TMP_VARIABLE(v))) \
        { \
           *TMP_VARIABLE(0) = TMP_VARIABLE(e); \
           ++TMP_VARIABLE(0); \
        } \
    } while (0); \
} while (0)

#define VECTOR_CLEAR(_v) \
(void) ( \
    (_v)->size = 0u \
)

#endif
