#ifndef LIST_H_
#define LIST_H_

#include <stdlib.h>
#include "macro_util.h"
#include "iterator.h"

typedef struct clist_node_t
{
    void* value;
    struct clist_node_t* next;
    struct clist_node_t* last;
}*LIST_NODE;

typedef struct clist_t
{
    LIST_NODE begin;
    LIST_NODE rbegin;
    size_t size;
    const char* type;
}*LIST;
 
#define LIST_ITERATOR LIST_ITERATOR

#define LIST_ITERATOR_NEXT(x, type) ((x)->next)

#define LIST_ITERATOR_LAST(x, type) ((x)->last)

#define LIST_ITERATOR_DEREF(x, type) (*((type*)((x)->value)))

#define LIST_ELEMENT_TYPE(l) \
( \
    (l)->element_type \
)

#define LIST_BEGIN(l) \
( \
    (l)->begin \
)

#define LIST_END(l) \
( \
    (LIST_NODE)(NULL) \
)

#define LIST_FRONT(l, type) \
( \
   LIST_ITERATOR_DEREF((l)->begin, type) \
)

#define LIST_BACK(l, type) \
( \
   LIST_ITERATOR_DEREF((l)->rbegin, type) \
)

#define LIST_SIZE(l) \
( \
    (l)->size \
)

#define LIST_EMPTY(l) \
( \
    (l)->size == 0u \
)

#endif
