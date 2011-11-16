#include "vector.h"
#include "list.h"
#include "algorithm.h"

#include <stdio.h>
#include <string.h>



int ddd = 0;
int b = 0;
  
static void vector_array_test(void)
{
    VECTOR v;
    ARRAY a;
    int aa[5];

    VECTOR_INIT(v, int);
    VECTOR_RESIZE(v, 5, int);
    ARRAY_INIT(a, 5, int);

#define OUT(x) printf("%d\n", x)
#define IN(x) scanf("%d", &x)

    {
#define FILL(x) x = b++

    FOR_EACH(VECTOR_BEGIN(v), VECTOR_END(v), VECTOR_ITERATOR, int, FILL);
    FOR_EACH(ARRAY_RBEGIN(v, int), ARRAY_REND(v, int), REVERSE_ITERATOR(VECTOR), int, OUT);

    FOR_EACH(ARRAY_BEGIN(a), ARRAY_END(a), ARRAY_ITERATOR, int, FILL);
    FOR_EACH(ARRAY_BEGIN(a), ARRAY_END(a), ARRAY_ITERATOR, int, OUT);


    FOR_EACH(aa, aa + 5, ARRAY_ITERATOR, int, FILL);
    COPY(ARRAY_BEGIN(a), ARRAY_END(a), ARRAY_ITERATOR, int, aa, ITERATOR(ARRAY), int);
    FOR_EACH(aa, aa + 5, ARRAY_ITERATOR, int, OUT);

    COPY(aa, aa + 5, ITERATOR(ARRAY), int, v, BACK_INSERT_ITERATOR(VECTOR), int);
    FOR_EACH(VECTOR_BEGIN(v), VECTOR_END(v), VECTOR_ITERATOR, int, FILL);

// #undef FILL
    }
    
    {
        int *dest;
        FIND(aa, aa + 5, ARRAY_ITERATOR, int, 12, dest);
        printf("12 == %d\n", *dest);

#define IS_EVEN(x) (x % 2) == 0

        FIND_IF(aa, aa + 5, ARRAY_ITERATOR, int, IS_EVEN, dest);
        printf("10 == %d\n", *dest);

#undef IS_EVEN

    }

    VECTOR_POP_BACK(v);
    VECTOR_PUSH_BACK(v, 2, int);

    VECTOR_FRONT(v, int) = VECTOR_BACK(v, int) = 3;
    ARRAY_FRONT(a, int) = ARRAY_BACK(a, int) = 2;
    FOR_EACH(VECTOR_BEGIN(v), VECTOR_END(v), ITERATOR(VECTOR), int, OUT);
    FOR_EACH(ARRAY_BEGIN(a), ARRAY_END(a), ITERATOR(ARRAY), int, OUT);

    VECTOR_DESTROY(v);
    ARRAY_DESTROY(a);
}

static void list_test(void)
{
    LIST l;
    char *p = "1234567"; 
    LIST_INIT(l, int);
    LIST_PUSH_BACK(l, 0, int);
    LIST_PUSH_FRONT(l, 1, int);
    LIST_INSERT_N(l, LIST_BEGIN(l), 3, 3, int);
    LIST_INSERT_N(l, LIST_RBEGIN(l), 2, 2, int);
    FOR_EACH(LIST_BEGIN(l), LIST_END(l), ITERATOR(LIST), int, FILL);
    FOR_EACH(LIST_BEGIN(l), LIST_END(l), ITERATOR(LIST), int, OUT);
    FOR_EACH(LIST_RBEGIN(l), LIST_REND(l), REVERSE_ITERATOR(LIST), int, OUT);

    LIST_POP_BACK(l);
    LIST_POP_FRONT(l);
    LIST_PUSH_BACK(l, 0, int);
    LIST_PUSH_FRONT(l, 3, int);

    LIST_INSERT(l, (LIST_RBEGIN(l)), 92, int);
    
    LIST_ERASE(l, LIST_BEGIN(l));
    LIST_ERASE(l, LIST_RBEGIN(l));
    LIST_CLEAR(l);
    COPY(p, p + strlen(p), ITERATOR(ARRAY), char, l, BACK_INSERT_ITERATOR(LIST), int );
    FOR_EACH(LIST_BEGIN(l), LIST_END(l), ITERATOR(LIST), int, OUT);

    LIST_DESTROY(l);
}

int main()
{
    vector_array_test();
    list_test();
    return 0;
}
