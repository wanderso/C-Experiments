#include <stdio.h>
#include <stdlib.h>

int main()
{
   FILE * fp;

   fp = fopen ("file.txt", "w+");
   fprintf(fp, "%s %s %s %d %s\n", "We", "are", "in", 2016, "save us");
   
   fclose(fp);
   
   return(0);
}
