#ifndef ITERATOR_H_
#define ITERATOR_H_

#include "macro_util.h"

#define ITERATOR_NEXT(x) JOIN(x, _NEXT)

#define ITERATOR_NEXT_N(x) JOIN(x, _NEXT_N) 

#define ITERATOR_LAST(x) JOIN(x, _LAST) 

#define ITERATOR_DEREF(x) JOIN(x, _DEREF) 

#endif
