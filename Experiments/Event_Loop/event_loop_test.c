#include <stdio.h>
#include <stdlib.h>


int main()
{
   FILE *fr;
   int n;
   long elapsed_seconds;
   char line[80];

   fr = fopen ("events.dta", "r");

   while(fgets(line, 80, fr) != NULL)
   {
	 sscanf (line, "%ld", &elapsed_seconds);
	 printf ("%ld\n", elapsed_seconds);
   }
   
   fclose(fr);
   return 0;
}

