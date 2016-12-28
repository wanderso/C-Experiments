#include <stdio.h>
#include <stdlib.h>
int addInt(int, int);
int subInt(int, int);
int mulInt(int, int);

struct listener {
    int (*functionPtr) (int,int);
};

typedef struct event {
    struct listener *listenArray;
    int listenArrayLen;
    int curr_maxLen;
} event_t;

void newEvent(struct event);
void freeEvent(struct event);


void newEvent(event_t e)
{
    e.listenArrayLen = 0;
    e.curr_maxLen = 10;
    e.listenArray = (int *) calloc (e.curr_maxLen, sizeof(int));
}

void freeEvent(event_t e)
{
    free(e.listenArray);
}

int addInt(int n, int m) {
    return n+m;
}

int subInt(int n, int m) {
    return n-m;
}

int mulInt(int n, int m) {
    return n*m;
}

int main () {

    struct listener l1, l2;

    //int (*fncPtr) (int,int);
    
    l1.functionPtr = &addInt;
    
    printf("Testing: %d\n", l1.functionPtr(addInt(5,2),9));
    
    l2.functionPtr = &mulInt;
    
    printf("Testing: %d\n", l2.functionPtr(addInt(5,2),9));
    
    return 0;
}


