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
    struct clist_node_t* prev;
}*LIST_NODE;

#define LIST_NODE_DESTROY(_node) \
(void) ( \
    free(_node->data), \
    free(_node) \
)

#define LIST_NODE_CREATE(_node, _value, _type) \
(void)( \
    ((_node) = (LIST_NODE)malloc(sizeof(*(_node)))), \
    ((_node)->data = malloc(sizeof(_type))), \
    (*((_type*)((_node)->data)) = (_value)) \
)

#define LIST_NODE_CREATE_N(_first, _last, _n, _value, _type) \
do \
{ \
    LIST_NODE TMP_VARIABLE(la); \
    LIST_NODE_CREATE(TMP_VARIABLE(la), (_value), _type); \
    _first = TMP_VARIABLE(la); \
    --(_n); \
    while((_n) != 0) \
    { \
        LIST_NODE_CREATE((TMP_VARIABLE(la)->next), (_value), _type); \
        TMP_VARIABLE(la)->next->prev = TMP_VARIABLE(la); \
        TMP_VARIABLE(la) = TMP_VARIABLE(la)->next; \
        --(_n); \
    } \
    _last = TMP_VARIABLE(la); \
} while (0)

typedef struct clist_t
{
    LIST_NODE begin;
    LIST_NODE rbegin;
    size_t size;
    const char* element_type;
}*LIST;

typedef LIST_NODE LIST_ITERATOR;

#define LIST_ITERATOR_INCREMENT(x, _type) (x = ((LIST_NODE)(x))->next)

#define LIST_ITERATOR_DECREMENT(x, _type) (x = ((LIST_NODE)(x))->prev)

#define LIST_ITERATOR_VALUE_REF(x, _type) (*((_type*)(((LIST_NODE)(x))->data)))

#define LIST_ITERATOR_VALUE_SET(x, _value, _type) ((*((_type*)(((LIST_NODE)(x))->data))) = (type)(_value))

typedef LIST_ITERATOR LIST_REVERSE_ITERATOR;

#define LIST_REVERSE_ITERATOR_INCREMENT(x, _type) LIST_ITERATOR_DECREMENT(x, _type)

#define LIST_REVERSE_ITERATOR_DECREMENT(x, _type) LIST_ITERATOR_INCREMENT(x, _type)

#define LIST_REVERSE_ITERATOR_VALUE_REF(x, _type) LIST_ITERATOR_VALUE_REF(x, _type)

#define LIST_REVERSE_ITERATOR_VALUE_SET(x, _value, _type) LIST_ITERATOR_VALUE_SET(x, _value, _type)

typedef LIST LIST_BACK_INSERT_ITERATOR;

#define LIST_BACK_INSERT_ITERATOR_INCREMENT(x, type) ((void)(0))

#define LIST_BACK_INSERT_ITERATOR_VALUE_SET(x, value, type) LIST_PUSH_BACK(x, value, type)

typedef LIST LIST_FRONT_INSERT_ITERATOR;

#define LIST_FRONT_INSERT_ITERATOR_INCREMENT(x, type) ((void)(0))

#define LIST_FRONT_INSERT_ITERATOR_VALUE_SET(x, value, type) LIST_PUSH_FRONT(x, value, type)


#define LIST_ELEMENT_TYPE(_l) \
( \
    CONST_VALUE((_l)->element_type, const char*) \
)

#define LIST_BEGIN(_l) \
( \
    CONST_VALUE((_l)->begin, LIST_ITERATOR) \
)

#define LIST_RBEGIN(_l) \
( \
    CONST_VALUE((_l)->rbegin, LIST_ITERATOR) \
)

#define LIST_END(_l) \
( \
    NULL \
)

#define LIST_REND(_l) \
( \
    NULL \
)

#define LIST_FRONT(_l, _type) \
( \
   *((_type*)((_l)->begin->data)) \
)

#define LIST_BACK(_l, _type) \
( \
   *((_type*)((_l)->rbegin->data)) \
)

#define LIST_SIZE(_l) \
( \
    CONST_VALUE((_l)->size, size_t) \
)

#define LIST_EMPTY(_l) \
( \
    (_l)->size == 0u \
)

#define LIST_INIT(_l, _type) \
(void) ( \
    (_l) = (LIST)(malloc(sizeof(*(_l)))), \
    (_l)->begin = (_l)->rbegin = NULL, \
    (_l)->size = 0u, \
    (_l)->element_type = TO_STRING(_type) \
)

#define LIST_DESTROY(_l) \
do \
{ \
    LIST_NODE TMP_VARIABLE(0) = (_l)->begin, TMP_VARIABLE(1); \
    while(TMP_VARIABLE(0) != NULL) \
    { \
        TMP_VARIABLE(1) = TMP_VARIABLE(0)->next; \
        LIST_NODE_DESTROY(TMP_VARIABLE(0)); \
        TMP_VARIABLE(0) = TMP_VARIABLE(1); \
    } \
    free(_l); \
    _l = NULL; \
}while(0)

#define LIST_PUSH_BACK(_l, _value, _type) \
do \
{ \
    LIST_NODE TMP_VARIABLE(tmp); \
    LIST const TMP_VARIABLE(l) = (_l); \
    LIST_NODE_CREATE(TMP_VARIABLE(tmp), (_value), _type); \
    TMP_VARIABLE(tmp)->next = NULL; \
\
    if(TMP_VARIABLE(l)->begin == NULL) \
    { \
        TMP_VARIABLE(tmp)->prev = NULL; \
        TMP_VARIABLE(l)->begin = TMP_VARIABLE(l)->rbegin = TMP_VARIABLE(tmp); \
    } \
    else \
    { \
        TMP_VARIABLE(tmp)->prev = TMP_VARIABLE(l)->rbegin; \
        TMP_VARIABLE(l)->rbegin->next = TMP_VARIABLE(tmp); \
        TMP_VARIABLE(l)->rbegin = TMP_VARIABLE(tmp); \
    } \
    ++(TMP_VARIABLE(l)->size); \
}while(0)

#define LIST_PUSH_FRONT(_l, _value, _type) \
do \
{ \
    LIST_NODE TMP_VARIABLE(tmp); \
    LIST const TMP_VARIABLE(l) = (_l); \
    LIST_NODE_CREATE(TMP_VARIABLE(tmp), (_value), _type); \
    TMP_VARIABLE(tmp)->prev = NULL; \
\
    if(TMP_VARIABLE(l)->rbegin == NULL) \
    { \
        TMP_VARIABLE(tmp)->next = NULL; \
        TMP_VARIABLE(l)->rbegin = TMP_VARIABLE(l)->begin = TMP_VARIABLE(tmp); \
    } \
    else \
    { \
        TMP_VARIABLE(tmp)->next = TMP_VARIABLE(l)->begin; \
        TMP_VARIABLE(l)->begin->prev = TMP_VARIABLE(tmp); \
        TMP_VARIABLE(l)->begin = TMP_VARIABLE(tmp); \
    } \
    ++(TMP_VARIABLE(l)->size); \
}while(0)

#define LIST_POP_BACK(_l) \
do \
{ \
    LIST const TMP_VARIABLE(l) = (_l); \
    assert(TMP_VARIABLE(l)->begin != NULL); \
    if (TMP_VARIABLE(l)->begin == TMP_VARIABLE(l)->rbegin) \
    { \
        LIST_NODE_DESTROY(TMP_VARIABLE(l)->begin); \
        TMP_VARIABLE(l)->begin = TMP_VARIABLE(l)->rbegin = NULL; \
    } \
    else \
    { \
        TMP_VARIABLE(l)->rbegin = TMP_VARIABLE(l)->rbegin->prev; \
        LIST_NODE_DESTROY(TMP_VARIABLE(l)->rbegin->next); \
        TMP_VARIABLE(l)->rbegin->next = NULL; \
    } \
} while (0)


#define LIST_POP_FRONT(_l) \
do \
{ \
    LIST const TMP_VARIABLE(l) = (_l); \
    assert(TMP_VARIABLE(l)->begin != NULL); \
    if (TMP_VARIABLE(l)->begin == TMP_VARIABLE(l)->rbegin) \
    { \
        LIST_NODE_DESTROY(TMP_VARIABLE(l)->begin); \
        TMP_VARIABLE(l)->begin = TMP_VARIABLE(l)->rbegin = NULL; \
    } \
    else \
    { \
        TMP_VARIABLE(l)->begin = TMP_VARIABLE(l)->begin->next; \
        LIST_NODE_DESTROY(TMP_VARIABLE(l)->begin->prev); \
        TMP_VARIABLE(l)->begin->prev = NULL; \
    } \
} while (0)

#define LIST_INSERT(_l, _iterator_insert, _value, _type) \
do \
{ \
    LIST const TMP_VARIABLE(l) = (_l); \
    LIST_ITERATOR const TMP_VARIABLE(iterator_insert) = (_iterator_insert); \
    LIST_ITERATOR TMP_VARIABLE(tmp); \
    LIST_NODE_CREATE(TMP_VARIABLE(tmp), (_value), _type); \
\
    if (TMP_VARIABLE(iterator_insert)->next != NULL) \
    { \
        TMP_VARIABLE(iterator_insert)->next->prev = TMP_VARIABLE(tmp); \
    } \
    else \
    { \
        TMP_VARIABLE(l)->rbegin = TMP_VARIABLE(tmp);\
    } \
    TMP_VARIABLE(tmp)->prev = TMP_VARIABLE(iterator_insert); \
    TMP_VARIABLE(tmp)->next = TMP_VARIABLE(iterator_insert)->next; \
    TMP_VARIABLE(iterator_insert)->next = TMP_VARIABLE(tmp); \
} while (0)

#define LIST_INSERT_N(_l, _iterator_insert, _n, _value, _type) \
do \
{ \
    LIST const TMP_VARIABLE(l) = (_l); \
    size_t TMP_VARIABLE(n) = (_n); \
    assert(TMP_VARIABLE(n) > 0); \
    if (TMP_VARIABLE(n) != 0) \
    { \
        LIST_ITERATOR TMP_VARIABLE(begin), TMP_VARIABLE(end); \
        LIST_ITERATOR const TMP_VARIABLE(iterator_insert) = (_iterator_insert); \
        LIST_NODE_CREATE_N(TMP_VARIABLE(begin), TMP_VARIABLE(end), TMP_VARIABLE(n), (_value), _type); \
        if (TMP_VARIABLE(iterator_insert)->next != 0) \
        { \
            TMP_VARIABLE(iterator_insert)->next->prev = TMP_VARIABLE(end); \
        } \
        else \
        { \
            TMP_VARIABLE(l)->rbegin = TMP_VARIABLE(end); \
        } \
        TMP_VARIABLE(end)->next = TMP_VARIABLE(iterator_insert)->next; \
        TMP_VARIABLE(iterator_insert)->next = TMP_VARIABLE(begin); \
        TMP_VARIABLE(begin)->prev = TMP_VARIABLE(iterator_insert); \
        TMP_VARIABLE(l)->size += TMP_VARIABLE(n); \
    } \
} while (0)

#define LIST_ERASE(_l, _iterator_erase) \
do \
{ \
    LIST const TMP_VARIABLE(l) = (_l); \
    LIST_ITERATOR const TMP_VARIABLE(iterator_erase)= (LIST_ITERATOR)(_iterator_erase); \
    if (TMP_VARIABLE(iterator_erase)->next != NULL) \
    { \
        TMP_VARIABLE(iterator_erase)->next->prev = TMP_VARIABLE(iterator_erase)->prev; \
    } \
    else \
    { \
        TMP_VARIABLE(l)->rbegin = TMP_VARIABLE(l)->rbegin->prev; \
    } \
    if (TMP_VARIABLE(iterator_erase)->prev != NULL) \
    { \
        TMP_VARIABLE(iterator_erase)->prev->next = TMP_VARIABLE(iterator_erase)->next; \
    } \
    else \
    { \
        TMP_VARIABLE(l)->begin = TMP_VARIABLE(l)->begin->next; \
    } \
    LIST_NODE_DESTROY(TMP_VARIABLE(iterator_erase)); \
    --(TMP_VARIABLE(l)->size); \
} while (0)

#define LIST_CLEAR(_l) \
do \
{ \
    LIST const TMP_VARIABLE(l) = (_l); \
    LIST_NODE TMP_VARIABLE(0) = TMP_VARIABLE(l)->begin, TMP_VARIABLE(1); \
    while(TMP_VARIABLE(0) != NULL) \
    { \
        TMP_VARIABLE(1) = TMP_VARIABLE(0)->next; \
        LIST_NODE_DESTROY(TMP_VARIABLE(0)); \
        TMP_VARIABLE(0) = TMP_VARIABLE(1); \
    } \
    TMP_VARIABLE(l)->begin = TMP_VARIABLE(l)->rbegin = NULL; \
    TMP_VARIABLE(l)->size = 0u; \
}while(0)

#endif
