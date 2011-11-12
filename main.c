#include "vector.h"
#include "list.h"
#include "algorithm.h"
#include <stdio.h>
int main()
{
    
    VECTOR v;
    int b = 0;
    int *dest;
    int d[20];
    VECTOR_INIT(v, int);
    VECTOR_RESIZE(v, 5, int);

#define OUT(x) printf("%d\n", x)
#define IN(x) scanf("%d", &x)

//     FOR_EACH(VECTOR_BEGIN(v, int), VECTOR_END(v, int), VECTOR_ITERATOR, int, IN);
//     FOR_EACH(VECTOR_BEGIN(v, int), VECTOR_END(v, int), VECTOR_ITERATOR, int, OUT);

#define FILL(x) x = b++
    FOR_EACH(VECTOR_BEGIN(v, int), VECTOR_END(v, int), VECTOR_ITERATOR, int, FILL);
    FOR_EACH(VECTOR_BEGIN(v, int), VECTOR_END(v, int), VECTOR_ITERATOR, int, OUT);

    VECTOR_DESTROY(v);

    FOR_EACH(d, d + 20, ARRAY_ITERATOR, int, FILL);
    FOR_EACH(d, d + 20, ARRAY_ITERATOR, int, OUT);

    FIND(d, d + 20, ARRAY_ITERATOR, int, 12, dest);
    printf("12 == %d\n", *dest);

#define EVEN(x) (x % 2) == 0
    FIND_IF(d, d + 20, ARRAY_ITERATOR, int, EVEN, dest);
    printf("6 == %d\n", *dest);


    return 0;
}
