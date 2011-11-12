#ifndef LIST_H_
#define LIST_H_

#include <stdlib.h>
#include "macro_util.h"
#include "iterator.h"

typedef struct clist_node_t
{
    void* data;
    struct clist_node_t* next;
    struct clist_node_t* last;
}*LIST_NODE;

#define LIST_NODE_DESTROY(node) \
( \
    free(node->data), \
    free(node), \
    (node) \
)

#define LIST_NODE_CREATE(node, value, type) \
( \
    (node) = (LIST_NODE)malloc(sizeof(*(node))), \
    (node)->data = malloc(sizeof(type)), \
    *((type*)((node)->data)) = (value), \
    (node)->next = (node)->last = NULL, \
    (node) \
)


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

#define LIST_INIT(l, type) \
(void) ( \
    (l) = (LIST)(malloc(sizeof(*(l)))), \
    (l)->begin = (l)->rbegin = NULL, \
    (l)->size = 0u, \
    (l)->element_type = TO_STRING(type) \
)

#define LIST_DESTROY(l) \
do \
{ \
    LIST_NODE tmp1 = (l)->begin; \
    LIST_NODE tmp2 = NULL; \
    while(tmp1 != NULL) \
    { \
        tmp2 = tmp1->next; \
        (LIST_NODE_DESTROY(tmp1)) = tmp2; \
    } \
    free(l); \
    l = NULL; \
)while(0)

#define LIST_PUSH_BACK(l, value, type) \
( \
    ( \
        ((l)->begin == NULL) ? \
            (l)->begin = (LIST_NODE_CREATE((l)->rbegin, (value), type)) : \
            (LIST_NODE_CREATE((l)->rbegin->next, (value), type))->last = (l)->rbegin, (l)->rbegin= (l)->rbegin->next \
    ), \
    ++((l)->size), \
    (l)->rbegin \
)

#define LIST_PUSH_FRONT(l, value, type) \
( \
    ( \
        ((l)->begin == NULL) ? \
            (l)->begin = (LIST_NODE_CREATE((l)->rbegin, (value), type)) : \
            (LIST_NODE_CREATE((l)->begin->last, (value), type))->next = (l)->begin, (l)->begin= (l)->begin->last \
    ), \
    ++((l)->size), \
    (l)->begin \
)

#define LIST_POP_BACK(l) \
(void) ( \
    ( \
        ((l)->begin == (l)->rbegin) ? \
            LIST_NODE_DESTROY((l)->begin), (l)->begin = (l)->rbegin = NULL : \
            (l)->rbegin = (l)->rbegin->last, (LIST_NODE_DESTROY((l)->rbegin->next)) = NULL \
    ), \
    --((l)->size) \
)

#define LIST_POP_FRONT(l) \
(void) ( \
    ( \
        ((l)->begin == (l)->rbegin) ? \
            LIST_NODE_DESTROY((l)->begin), (l)->begin = (l)->rbegin = NULL : \
            (l)->begin = (l)->begin->next, (LIST_NODE_DESTROY((l)->begin->last)) = NULL \
    ), \
    --((l)->size) \
)

#define LIST_CLEAR(l) \
do \
{ \
    LIST_NODE tmp1 = (l)->begin; \
    LIST_NODE tmp2 = NULL; \
    while(tmp1 != NULL) \
    { \
        tmp2 = tmp1->next; \
        (LIST_NODE_DESTROY(tmp1)) = tmp2; \
    } \
    (l)->begin = (l)->rbegin = NULL; \
    (l)->size = 0u; \
)while(0)

#endif
