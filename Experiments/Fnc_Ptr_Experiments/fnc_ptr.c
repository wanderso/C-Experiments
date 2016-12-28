#include <stdio.h>

int addInt(int, int);
int subInt(int, int);
int mulInt(int, int);


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
    int (*fncPtr) (int,int);
    
    fncPtr = &addInt;
    
    printf("Testing: %d\n", fncPtr(addInt(5,2),9));
    
    fncPtr = &mulInt;
    
    printf("Testing: %d\n", fncPtr(addInt(5,2),9));
    
    return 0;
}


