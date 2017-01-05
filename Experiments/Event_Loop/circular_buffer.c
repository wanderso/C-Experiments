#include <stdio.h>
#include <stdint.h>

typedef struct
{
    uint8_t * const buffer;
    int head;
    int tail;
    const int maxLen;
} hicircBuf_t;

int main ()
{
    FILE *fp;
    float c, d;
  
    fp = fopen("microphone.csv","r");
    for ( ; fscanf(fp, "%f,%f", &c, &d) != EOF; ) 
    {
        printf("%f\n", d); 
    }
    fclose(fp);
   
    return(0);
}

