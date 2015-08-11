#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

void pints(unsigned int max, ...)
{
  va_list vl;
  va_start(vl, max);
  unsigned int i = 0;
  for(; i < max; i++) printf("%i,", va_arg(vl, int));
  printf("\b\n");
  va_end(vl);
}

double f(double (*fin)(double), int argv, ...)
{
  double rv = 0.0;
  va_list vl;
  va_start(vl, argv);
  unsigned int i;
  for(i = 0; i < argv; i++) rv += fin(va_arg(vl, double));
  printf("\b\n");
  va_end(vl);
  return rv;
}

int main()
{

  pints(4, 2, 5, 6, 4);

  printf("select from: \n");
  char * arr[] = {"sin", "cos", "tan"};
  double ( * Farr [ ] ) ( double ) = {sin, cos, tan};
  int num_functions = 3;
  int selection = 0;
  unsigned int i;
  for(i = 0; i < num_functions; i++)
  {
    printf("%i. %s\n", i, arr[i]);
  }
  printf("enter selection: "); scanf("%d", &selection);
  if(selection >= 0 && selection < num_functions)
  {
    double i;
    printf("%lf\n", f(Farr[selection], 3, 2.0, 4.0, 6.0));
  }


  return 0;
}
