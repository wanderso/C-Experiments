#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct
{
    float * buffer;
    int head;
    int tail;
    int maxLen;
} circBuf_t;

void cb_init(circBuf_t *cb, int capacity)
{
    cb->buffer = (float *) calloc (capacity, sizeof(float));
    cb->maxLen = capacity;
}

void cb_add(circBuf_t *cb, float f)
{
    cb->tail += 1;
    cb->tail = cb->tail % cb->maxLen;
    cb->buffer[cb->tail] = f;
}

void cb_free(circBuf_t *cb)
{
    free(cb->buffer);
}

int main ()
{
    circBuf_t cb;
    FILE *fp;
    float c, d;
    
    cb_init(&cb, 1024);
    
    cb_add(&cb, 1.000);
  
    fp = fopen("microphone.csv","r");
    for ( ; fscanf(fp, "%f,%f", &c, &d) != EOF; ) 
    {
        //printf("%f\n", d); 
    }
    fclose(fp);
    
    cb_free(&cb);
   
    return(0);
}

