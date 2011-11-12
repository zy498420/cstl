#include "vector.h"
#include "list.h"
#include "algorithm.h"
#include <stdio.h>

#define OUT(x) printf("%d\n", x)
#define IN(x) scanf("%d", &x)

void vector_array_test(void);
void list_test(void);
  
void vector_array_test(void)
{
    VECTOR v;
    ARRAY a;
    int b = 0;
    int aa[5];

    VECTOR_INIT(v, int);
    VECTOR_RESIZE(v, 5, int);
    ARRAY_INIT(a, 5, int);
    {
#define FILL(x) x = b++

    FOR_EACH(VECTOR_BEGIN(v), VECTOR_END(v), VECTOR_ITERATOR, int, FILL);
    FOR_EACH(VECTOR_BEGIN(v), VECTOR_END(v), VECTOR_ITERATOR, int, OUT);

    FOR_EACH(ARRAY_BEGIN(a), ARRAY_END(a), ARRAY_ITERATOR, int, FILL);
    FOR_EACH(ARRAY_BEGIN(a), ARRAY_END(a), ARRAY_ITERATOR, int, OUT);


    FOR_EACH(aa, aa + 5, ARRAY_ITERATOR, int, FILL);
    FOR_EACH(aa, aa + 5, ARRAY_ITERATOR, int, OUT);

#undef FILL
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

    VECTOR_DESTROY(v);
    ARRAY_DESTROY(a);
}

void list_test(void)
{
    LIST l;
    LIST_INIT(l, int);
    LIST_PUSH_BACK(l, 0, int);
    LIST_PUSH_FRONT(l, 1, int);
    FOR_EACH(LIST_BEGIN(l), LIST_END(l), LIST_ITERATOR, int, OUT);
    LIST_POP_BACK(l);
    LIST_CLEAR(l);
    LIST_DESTROY(l);

}

int main()
{
    vector_array_test();
    list_test();

    return 0;
}
