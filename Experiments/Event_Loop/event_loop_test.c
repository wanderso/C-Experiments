#include <stdio.h>
#include <stdlib.h>


int main()
{
   FILE *fr;
   int n;
   long elapsed_seconds;
   char line[80];

   fr = fopen ("elapsed.dta", "r");  /* open the file for reading */
   /* elapsed.dta is the name of the file */
   /* "rt" means open the file for reading text */

   while(fgets(line, 80, fr) != NULL)
   {
	 sscanf (line, "%ld", &elapsed_seconds);
	 printf ("%ld\n", elapsed_seconds);
   }
   fclose(fr);  /* close the file prior to exiting the routine */
   return 0;

}

