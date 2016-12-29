#include <stdio.h>
#include <stdlib.h>

#define LIFE_WORTH_LIVING 0
#define DEFAULT_ARRAY_LENGTH 10
#define ARRAY_LENGTH_STEP 5

typedef struct array {
    int * array;
    int arrayLen;
    int curr_maxLen;
} array_t;

array_t newArray(void) {
    array_t createArray;
    createArray.array = (int*) calloc (DEFAULT_ARRAY_LENGTH,sizeof(int));
    createArray.arrayLen = 0;
    createArray.curr_maxLen = DEFAULT_ARRAY_LENGTH;
    return createArray;
}

void destroyArray(array_t target)
{
    free (target.array);
}

int main() {
    array_t arrv;
    arrv = newArray();
    printf("%p,%d,%d\n", arrv.array, arrv.arrayLen, arrv.curr_maxLen);
    destroyArray(arrv);
    return 0;
}
