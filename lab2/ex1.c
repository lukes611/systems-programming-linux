#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
  double start, end, inc;
  printf("enter starting value of x:");
  scanf("%lf", &start);
  printf("enter ending value of x:");
  scanf("%lf", &end);
  printf("enter increment:");
  scanf("%lf", &inc);
  if((inc > 0.0 && end > start) || (inc < 0.0 && end < start))
  {
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
      for(i = start; i <= end; i += inc) printf("%lf\n", Farr[selection](i));
    }

  }
  return 0;
}
