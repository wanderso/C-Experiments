#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    float * buffer;
    int head;
    int tail;
    int maxLen;
} circBuf_t;

void cb_init(circBuf_t *cb, int capacity, float init)
{
    cb->buffer = (float *) calloc (capacity, sizeof(float));
    cb->maxLen = capacity;
    for(int i = 0; i < capacity; i++)
    {
        cb->buffer[i] = init;
    }
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
    int len, primary_window, secondary_window;
    float * traveler;
    float count;
    
    /* Set start to a number between 0 and maxLen */
    len = cb->maxLen;
    start = start % len;
    if (start < 0)
    {
        start += len;
    }
    
    /* If the window wraps around the buffer, take care of that */    
    primary_window = window;
    secondary_window = 0;
    
    if (start+window > len)
    {
        secondary_window = start+window - len;
        primary_window = primary_window - secondary_window;
    }
    
    /* Initialize the traveling pointer and the total count */
    traveler = cb->buffer + start;
    count = 0; 
    
    /* Loop from the traveler to the end of the window OR the buffer */
    for (int i = 0; i < primary_window; i++)
    {
        count += *traveler;
        traveler++;
    }
    
    /* Loop from the start of the buffer to the end of the window if needed */
    traveler = cb->buffer;
    for (int i = 0; i < secondary_window; i++)
    {
        count += *traveler;
        traveler++;
    }
    
    /* Return count/window */
    return count/window;
}

float cb_dis_avg(circBuf_t *cb, float displace, int start, int window)
{
    int len, primary_window, secondary_window;
    float * traveler;
    float count;
    
    /* Set start to a number between 0 and maxLen */
    len = cb->maxLen;
    start = start % len;
    if (start < 0)
    {
        start += len;
    }
    
    /* If the window wraps around the buffer, take care of that */    
    primary_window = window;
    secondary_window = 0;
    
    if (start+window > len)
    {
        secondary_window = start+window - len;
        primary_window = primary_window - secondary_window;
    }
    
    /* Initialize the traveling pointer and the total count */
    traveler = cb->buffer + start;
    count = 0; 
    
    /* Loop from the traveler to the end of the window OR the buffer */
    for (int i = 0; i < primary_window; i++)
    {
        count += *traveler - displace;
        traveler++;
    }
    
    /* Loop from the start of the buffer to the end of the window if needed */
    traveler = cb->buffer;
    for (int i = 0; i < secondary_window; i++)
    {
        count += *traveler - displace;
        traveler++;
    }
    
    /* Return count/window */
    return count/window;
    
}

float cb_noi_avg(circBuf_t *cb, float floor, int start, int window)
{
    int len, primary_window, secondary_window;
    float * traveler;
    float count;
    
    /* Set start to a number between 0 and maxLen */
    len = cb->maxLen;
    start = start % len;
    if (start < 0)
    {
        start += len;
    }
    
    /* If the window wraps around the buffer, take care of that */    
    primary_window = window;
    secondary_window = 0;
    
    if (start+window > len)
    {
        secondary_window = start+window - len;
        primary_window = primary_window - secondary_window;
    }
    
    /* Initialize the traveling pointer and the total count */
    traveler = cb->buffer + start;
    count = 0; 
    
    /* Loop from the traveler to the end of the window OR the buffer */
    for (int i = 0; i < primary_window; i++)
    {
        count += fabsf(*traveler - floor);
        traveler++;
    }
    
    /* Loop from the start of the buffer to the end of the window if needed */
    traveler = cb->buffer;
    for (int i = 0; i < secondary_window; i++)
    {
        count += fabsf(*traveler - floor);
        traveler++;
    }
    
    /* Return count/window */
    return count/window;
    
}

int main ()
{
    circBuf_t cb;
    FILE *fp;
    float c, d;
    
    int count, interval, window, length;
    
    length = 1024; // Length of circ_buf
    interval = 4;
    window = 8;
    
    cb_init(&cb, length, 1.0);
    
  
    fp = fopen("microphone.csv","r");
    count = 0;
    for ( ; fscanf(fp, "%f,%f", &c, &d) != EOF; ) 
    {
        cb_add(&cb, d);
        count++;
        if (count == interval)
        {
            float sound = cb_noi_avg(&cb, 1.0, (cb.tail-interval), window);
            printf("Time: %f Output: %f\n", c, sound);
            /*if (sound > 0.05)
            {
                printf("Sound detected at time %f\n", c);
            }*/
            count = 0;
        }
    }
    fclose(fp);
    
    printf("Average of first 128: %f\n", cb_avg(&cb, 0, 128));
    
    printf("Displace average of first 128: %f\n", cb_dis_avg(&cb, 1.0, 0, 128));
    
    printf("Noise average of first 128: %f\n", cb_noi_avg(&cb, 1.0, 0, 128));


    
    cb_free(&cb);
   
    return(0);
}

