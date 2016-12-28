#include <stdio.h>


struct event {
    int pin;
    int status;
};

struct listener {
    int (*functionPtr)(struct event,struct event);
};


int main () {
   struct event z;
   z.pin = 4;
   z.status = 5;
   
   printf("%d,%d\n", z.pin, z.status);
   
   return 0;
}


