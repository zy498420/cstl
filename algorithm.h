#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include "iterator.h"

#define FOR_EACH(input_iterator_first, input_iterator_last, input_iterator_type, input_value_type, functor)  \
do \
{ \
    input_iterator_type TMP_VARIABLE(i) = input_iterator_first; \
    input_iterator_type const TMP_VARIABLE(e) = input_iterator_last; \
\
    while(TMP_VARIABLE(i) != TMP_VARIABLE(e) ) \
    { \
        functor(ITERATOR_VALUE_REF(input_iterator_type)(TMP_VARIABLE(i), input_value_type)); \
        TMP_VARIABLE(i) = (ITERATOR_NEXT(input_iterator_type)(TMP_VARIABLE(i), input_value_type)); \
    } \
} while(0) 

#define COPY(input_iterator_first, input_iterator_last, input_iterator_type, input_value_type, \
    output_iterator_first, output_iterator_type, output_value_type) \
do \
{ \
    input_iterator_type  TMP_VARIABLE(i) = input_iterator_first; \
    input_iterator_type const TMP_VARIABLE(e) = input_iterator_last; \
    output_iterator_type TMP_VARIABLE(o) = output_iterator_first; \
\
    while(TMP_VARIABLE(i) != TMP_VARIABLE(e) ) \
    { \
        ITERATOR_VALUE_REF(output_iterator_type)(TMP_VARIABLE(o), output_value_type) = \
            ITERATOR_VALUE_REF(input_iterator_type)(TMP_VARIABLE(i), input_value_type); \
        TMP_VARIABLE(i) = (ITERATOR_NEXT(input_iterator_type)(TMP_VARIABLE(i), input_value_type)); \
        TMP_VARIABLE(o) = (ITERATOR_NEXT(output_iterator_type)(TMP_VARIABLE(o), output_value_type)); \
    } \
} while(0) 

#define FIND(input_iterator_first, input_iterator_last, input_iterator_type, input_value_type, value, result) \
do \
{ \
    input_iterator_type const TMP_VARIABLE(e) = input_iterator_last; \
    input_value_type const TMP_VARIABLE(v) = value; \
    result = (input_iterator_first); \
\
    while(result != (TMP_VARIABLE(e)) && (ITERATOR_VALUE_REF(input_iterator_type)(result, input_value_type)) != TMP_VARIABLE(v)) \
    { \
        result = (ITERATOR_NEXT(input_iterator_type)(result, input_value_type)); \
    }\
} while(0)

#define FIND_IF(input_iterator_first, input_iterator_last, input_iterator_type, input_value_type, predicate, result) \
do \
{ \
    input_iterator_type const TMP_VARIABLE(e) = input_iterator_last; \
    result = (input_iterator_first); \
    while(result != (TMP_VARIABLE(e)) && (!(predicate(ITERATOR_VALUE_REF(input_iterator_type)(result, input_value_type))))) \
    { \
        result = (ITERATOR_NEXT(input_iterator_type)(result, input_value_type)); \
    }\
} while(0)

#endif
