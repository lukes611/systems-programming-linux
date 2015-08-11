#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

int compare (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

int main(int argc, char * * argv)
{



  unsigned int n = (unsigned int)argc-1;
  unsigned int i = 0;
  //for(; i < argc; i++) printf("'%s\n'", argv[i]);
  if(n < 2) return 0;
  int * arr = (int *) malloc(4 * argc);
  for(i = 0; i < n; i++) arr[i] = atoi(argv[i+1]);

  qsort(arr, n, 4, compare);

  for(i = 0; i < n; i++) printf("%i\n", arr[i]);

  free(arr);


  return 0;
}
