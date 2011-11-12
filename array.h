#ifndef ARRAY_H_
#define ARRAY_H_

#include "iterator.h"

#define ARRAY_ITERATOR ARRAY_ITERATOR     //to help IDE parse

#define ARRAY_ITERATOR_NEXT(x, type) ((x) + 1)

#define ARRAY_ITERATOR_LAST(x, type) ((x) - 1)

#define ARRAY_ITERATOR_NEXT_N(x, n, type) ((x) + n)

#define ARRAY_ITERATOR_DEREF(x, type) (*(x))

#endif
