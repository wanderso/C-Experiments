#include <stdio.h>
#include <stdlib.h>

int main()
{
   int i, j, n, m, x, y, z;
   int *a, *ptr;

   printf("Number of elements to be entered and number of iterations to run: ");
   scanf("%d %d",&n, &m);

   a = (int*)calloc(n, sizeof(int));
   printf("Enter 3 numbers between (1-%d) %d times:\n", n, m);
   for( i=0 ; i < m ; i++ ) 
   {
      scanf("%d %d %d", &x, &y, &z);
      ptr = a;
      ptr += y-1;
      for (j = y-1; j < z ; j++)
      {
		  *ptr += x;
		  ptr++;
	  }
   }

   printf("The array is: ");
   for( i=0 ; i < n ; i++ ) 
   {
      printf("%d ",a[i]);
   }
   free( a );
   printf("\n");
   
   return(0);
}
