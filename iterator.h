#ifndef ITERATOR_H_
#define ITERATOR_H_

#include "macro_util.h"

#define ITERATOR_NEXT(x) JOIN(x, _NEXT)

#define ITERATOR_NEXT_N(x) JOIN(x, _NEXT_N) 

#define ITERATOR_LAST(x) JOIN(x, _LAST) 

#define ITERATOR_VALUE_REF(x) JOIN(x, _VALUE_REF) 

typedef void *ARRAY_ITERATOR;   

#define ARRAY_ITERATOR_NEXT(x, type) ((type*)(x) + 1)

#define ARRAY_ITERATOR_LAST(x, type) ((type*)(x) - 1)

#define ARRAY_ITERATOR_NEXT_N(x, n, type) ((type*)(x) + n)

#define ARRAY_ITERATOR_VALUE_REF(x, type) (*((type*)(x)))

#endif
