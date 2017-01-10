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

float cb_avg(circBuf_t *cb, int start, int window)
{
    /* Set start to a number between 0 and maxLen */
    int len = cb->maxLen;
    start = start % len;
    if (start < 0)
    {
        start += len;
    }
    
    /* */
    
    int primary_window, secondary_window;
    
    primary_window = window;
    secondary_window = 0;
    
    if (start+window > len)
    {
        secondary_window = start+window - len;
        primary_window = primary_window - secondary_window;
    }
       
    float * traveler = cb->buffer + start;
    float count = 0; 
    for (int i = 0; i < primary_window; i++)
    {
        count += *traveler;
        traveler++;
    }
    traveler = cb->buffer;
    for (int i = 0; i < secondary_window; i++)
    {
        count += *traveler;
        traveler++;
    }
    
    printf("%d %d\n", primary_window, secondary_window);

    return count/window;
}

float cb_diff(circBuf_t *cb, int start, int window)
{
    float * traveler = cb->buffer + start;
}

int main ()
{
    circBuf_t cb;
    FILE *fp;
    float c, d;
    
    cb_init(&cb, 1024);
    
  
    fp = fopen("microphone.csv","r");
    for ( ; fscanf(fp, "%f,%f", &c, &d) != EOF; ) 
    {
        cb_add(&cb, d);
    }
    fclose(fp);
    
    printf("Average of first 1024: %f\n", cb_avg(&cb, 0, 1024));
    
    cb_free(&cb);
   
    return(0);
}

