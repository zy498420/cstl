#ifndef ITERATOR_H_
#define ITERATOR_H_

#include "macro_util.h"

/*Predefined iterators for containers*/
#define ITERATOR(x) JOIN(x, _ITERATOR) 

#define REVERSE_ITERATOR(x) JOIN(x, _REVERSE_ITERATOR)

#define BACK_INSERT_ITERATOR(x) JOIN(x, _BACK_INSERT_ITERATOR)

#define FRONT_INSERT_ITERATOR(x) JOIN(x, _FRONT_INSERT_ITERATOR)


/*all categories of iterator support*/
#define ITERATOR_INCREMENT(x) JOIN(x, _INCREMENT)

/*input iterator*/
#define ITERATOR_VALUE_REF(x) JOIN(x, _VALUE_REF)

/*output iterator*/
#define ITERATOR_VALUE_SET(x) JOIN(x, _VALUE_SET)

/*bidirectional iterator*/
#define ITERATOR_DECREMENT(x) JOIN(x, _DECREMENT)

/*random access iterator*/
#define ITERATOR_INCREMENT_N(x) JOIN(x, _INCREMENT_N) 



typedef void *ARRAY_ITERATOR;   

#define ARRAY_ITERATOR_INCREMENT(x, type) ((x) = (type*)(x) + 1)

#define ARRAY_ITERATOR_DECREMENT(x, type) ((x) = (type*)(x) - 1)

#define ARRAY_ITERATOR_INCREMENT_N(x, n, type) ((x) = (type*)(x) + n)

#define ARRAY_ITERATOR_VALUE_REF(x, type) (*((type*)(x)))

#define ARRAY_ITERATOR_VALUE_SET(x, value, type) ((*((type*)(x))) = (type)(value))


typedef ARRAY_ITERATOR ARRAY_REVERSE_ITERATOR;

#define ARRAY_REVERSE_ITERATOR_INCREMENT(x, type) ARRAY_ITERATOR_DECREMENT(x, type)

#define ARRAY_REVERSE_ITERATOR_DECREMENT(x, type) ARRAY_ITERATOR_INCREMENT(x, type)

#define ARRAY_REVERSE_ITERATOR_INCREMENT_N(x, n, type) ARRAY_ITERATOR_INCREMENT_N(x, (-(n)), type)

#define ARRAY_REVERSE_ITERATOR_VALUE_REF(x, type) ARRAY_ITERATOR_VALUE_REF(x, type)

#define ARRAY_REVERSE_ITERATOR_VALUE_SET(x, value, type) ARRAY_ITERATOR_VALUE_SET(x, value, type)

#endif
