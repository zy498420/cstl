#ifndef LIST_H_
#define LIST_H_

#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

#include "macro_util.h"
#include "iterator.h"

typedef struct clist_node_t
{
    void* data;
    struct clist_node_t* next;
    struct clist_node_t* last;
}*LIST_NODE;

#define LIST_NODE_DESTROY(node) \
(void) ( \
    free(node->data), \
    free(node), \
    node = NULL \
)

#define LIST_NODE_CREATE(node, value, type) \
( \
    (node) = (LIST_NODE)malloc(sizeof(*(node))), \
    (node)->data = malloc(sizeof(type)), \
    *((type*)((node)->data)) = (value), \
    (node)->next = (node)->last = NULL, \
    (node) \
)

typedef LIST_NODE LIST_ITERATOR;  

typedef struct clist_t
{
    LIST_NODE begin;
    LIST_NODE rbegin;
    size_t size;
    const char* element_type;
}*LIST;

#define LIST_ITERATOR_NEXT(x, type) (((LIST_NODE)(x))->next)

#define LIST_ITERATOR_LAST(x, type) (((LIST_NODE)(x))->last)

#define LIST_ITERATOR_VALUE_REF(x, type) (*((type*)(((LIST_NODE)(x))->data)))

#define LIST_ELEMENT_TYPE(l) \
( \
    CONST_VALUE((l)->element_type, const char*) \
)

#define LIST_BEGIN(l) \
( \
    CONST_VALUE((l)->begin, LIST_ITERATOR) \
)

#define LIST_RBEGIN(l) \
( \
    CONST_VALUE((l)->rbegin, LIST_ITERATOR) \
)

#define LIST_END(l) \
( \
    NULL \
)

#define LIST_REND(l) \
( \
    NULL \
)

#define LIST_FRONT(l, type) \
( \
   *((type*)((l)->begin->data)) \
)

#define LIST_BACK(l, type) \
( \
   *((type*)((l)->rbegin->data)) \
)

#define LIST_SIZE(l) \
( \
    CONST_VALUE((l)->size, size_t) \
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
    LIST_NODE TMP_VARIABLE(0) = (l)->begin, TMP_VARIABLE(1) = NULL; \
    while(TMP_VARIABLE(0) != NULL) \
    { \
        TMP_VARIABLE(1) = TMP_VARIABLE(0)->next; \
        LIST_NODE_DESTROY(TMP_VARIABLE(0)); \
        TMP_VARIABLE(0) = TMP_VARIABLE(1); \
    } \
    free(l); \
    l = NULL; \
}while(0)

#define LIST_PUSH_BACK(l, value, type) \
do{ \
    type TMP_VARIABLE(v) = (value); \
    ((l)->begin == NULL) ? \
        ((l)->begin = (LIST_NODE_CREATE((l)->rbegin, TMP_VARIABLE(v), type))) : \
        (((LIST_NODE_CREATE((l)->rbegin->next, TMP_VARIABLE(v), type))->last = (l)->rbegin), ((l)->rbegin = (l)->rbegin->next)); \
    ++((l)->size); \
}while(0)

#define LIST_PUSH_FRONT(l, value, type) \
do{ \
    type TMP_VARIABLE(v) = (value); \
    ((l)->begin == NULL) ? \
        ((l)->begin = (LIST_NODE_CREATE((l)->rbegin, TMP_VARIABLE(v), type))) : \
        (((LIST_NODE_CREATE((l)->begin->last, TMP_VARIABLE(v), type))->next = (l)->begin), ((l)->begin = (l)->begin->last)); \
    ++((l)->size); \
}while(0)

#define LIST_POP_BACK(l) \
(void) ( \
    assert((l)->begin != NULL), \
    ( \
        ((l)->begin == (l)->rbegin) ? \
            (void)((LIST_NODE_DESTROY((l)->begin)), ((l)->rbegin = NULL)) : \
            (void)(((l)->rbegin = (l)->rbegin->last), (LIST_NODE_DESTROY((l)->rbegin->next))) \
    ), \
    --((l)->size) \
)

#define LIST_POP_FRONT(l) \
(void) ( \
    assert((l)->begin != NULL), \
    ( \
        ((l)->begin == (l)->rbegin) ? \
            (void)((LIST_NODE_DESTROY((l)->begin)), ((l)->rbegin = NULL)) : \
            (void)(((l)->begin = (l)->begin->next), (LIST_NODE_DESTROY((l)->begin->last)))  \
    ), \
    --((l)->size) \
)

#define LIST_INSERT(l, iterator_insert, value, type) \
do \
{ \
    LIST_ITERATOR TMP_VARIABLE(i) = ((LIST_ITERATOR)(iterator_insert)); \
    LIST_ITERATOR TMP_VARIABLE(v) = NULL; \
    (void)LIST_NODE_CREATE(TMP_VARIABLE(v), (value), type); \
\
    if (TMP_VARIABLE(i)->next != NULL) \
    { \
        TMP_VARIABLE(i)->next->last = TMP_VARIABLE(v); \
    } \
    else \
    { \
        (l)->rbegin = TMP_VARIABLE(v);\
    } \
    TMP_VARIABLE(v)->last = TMP_VARIABLE(i); \
    TMP_VARIABLE(v)->next = TMP_VARIABLE(i)->next; \
    TMP_VARIABLE(i)->next = TMP_VARIABLE(v); \
} while (0)

#define LIST_ERASE(l, iterator_erase) \
do \
{ \
    LIST_ITERATOR TMP_VARIABLE(e)= (LIST_ITERATOR)(iterator_erase); \
    if (TMP_VARIABLE(e)->next != NULL) \
    { \
        TMP_VARIABLE(e)->next->last = TMP_VARIABLE(e)->last; \
    } \
    else \
    { \
        (l)->rbegin = (l)->rbegin->last; \
    } \
    if (TMP_VARIABLE(e)->last != NULL) \
    { \
        TMP_VARIABLE(e)->last->next = TMP_VARIABLE(e)->next; \
    } \
    else \
    { \
        (l)->begin = (l)->begin->next; \
    } \
    LIST_NODE_DESTROY(TMP_VARIABLE(e)); \
} while (0)

#define LIST_CLEAR(l) \
do \
{ \
    while((l)->begin != NULL) \
    { \
        LIST_NODE TMP_VARIABLE(1) = (l)->begin ->next; \
        LIST_NODE_DESTROY((l)->begin); \
        (l)->begin  = TMP_VARIABLE(1); \
    } \
    (l)->rbegin = NULL; \
    (l)->size = 0u; \
}while(0)

#endif
