#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include "iterator.h"

#define FOR_EACH(first, last, iterate, type, functor)  \
do \
{ \
    void* TMP_VARIABLE(_0) = (first); \
    while(TMP_VARIABLE(_0) != (void*)(last) ) \
    { \
        functor(ITERATOR_VALUE_REF(iterate)(TMP_VARIABLE(_0), type)); \
        TMP_VARIABLE(_0) = (ITERATOR_NEXT(iterate)(TMP_VARIABLE(_0), type)); \
    } \
} while(0) 

#define FIND(first, last, iterate, type, value, result) \
do \
{ \
    result = (first); \
    while(result != (last) && (ITERATOR_VALUE_REF(iterate)(result, type)) != (value)) \
    { \
        result = (ITERATOR_NEXT(iterate)(result, type)); \
    }\
} while(0)

#define FIND_IF(first, last, iterate, type, predicate, result) \
do \
{ \
    result = (first); \
    while(result != (last) && (!(predicate(ITERATOR_VALUE_REF(iterate)(result, type))))) \
    { \
        result = (ITERATOR_NEXT(iterate)(result, type)); \
    }\
} while(0)


#endif
