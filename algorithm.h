#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include "iterator.h"

#define FOR_EACH(input_iterator_first, input_iterator_last, input_iterator_type, input_value_type, _functor)  \
do \
{ \
    input_iterator_type TMP_VARIABLE(_first_) = input_iterator_first; \
    input_iterator_type const TMP_VARIABLE(_last_) = input_iterator_last; \
\
    while(TMP_VARIABLE(_first_) != TMP_VARIABLE(_last_) ) \
    { \
        _functor(ITERATOR_VALUE_REF(input_iterator_type)(TMP_VARIABLE(_first_), input_value_type)); \
        (ITERATOR_INCREMENT(input_iterator_type)(TMP_VARIABLE(_first_), input_value_type)); \
    } \
} while(0) 

#define COPY(input_iterator_first, input_iterator_last, input_iterator_type, input_value_type, \
    output_iterator_first, output_iterator_type, output_value_type) \
do \
{ \
    input_iterator_type  TMP_VARIABLE(_first_) = input_iterator_first; \
    input_iterator_type const TMP_VARIABLE(_last_) = input_iterator_last; \
    output_iterator_type TMP_VARIABLE(_output_) = output_iterator_first; \
\
    while(TMP_VARIABLE(_first_) != TMP_VARIABLE(_last_) ) \
    { \
        ITERATOR_VALUE_SET(output_iterator_type)(TMP_VARIABLE(_output_), \
            ITERATOR_VALUE_REF(input_iterator_type)(TMP_VARIABLE(_first_), input_value_type), \
            output_value_type); \
        (ITERATOR_INCREMENT(input_iterator_type)(TMP_VARIABLE(_first_), input_value_type)); \
        (ITERATOR_INCREMENT(output_iterator_type)(TMP_VARIABLE(_output_), output_value_type)); \
    } \
} while(0) 

#define FIND(input_iterator_first, input_iterator_last, input_iterator_type, input_value_type, _value, _result) \
do \
{ \
    input_iterator_type const TMP_VARIABLE(_last_) = input_iterator_last; \
    input_value_type const TMP_VARIABLE(v) = _value; \
    _result = (input_iterator_first); \
\
    while(_result != (TMP_VARIABLE(_last_)) && (ITERATOR_VALUE_REF(input_iterator_type)(_result, input_value_type)) != TMP_VARIABLE(v)) \
    { \
        (ITERATOR_INCREMENT(input_iterator_type)(_result, input_value_type)); \
    }\
} while(0)

#define FIND_IF(input_iterator_first, input_iterator_last, input_iterator_type, input_value_type, _predicate, _result) \
do \
{ \
    input_iterator_type const TMP_VARIABLE(_last_) = input_iterator_last; \
    _result = (input_iterator_first); \
    while(_result != (TMP_VARIABLE(_last_)) && (!(_predicate(ITERATOR_VALUE_REF(input_iterator_type)(_result, input_value_type))))) \
    { \
        (ITERATOR_INCREMENT(input_iterator_type)(_result, input_value_type)); \
    }\
} while(0)

#endif
