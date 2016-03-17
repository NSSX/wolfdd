#include "my_h.h"

int                     event_mlx(int keycode, t_struct *mystruct)
{
  if (keycode == 65307)
    exit(1);
  return (0);
}

double mypow(int a, int n)
{
  double res;
  int i;

  i = 1;
  res = a;
  while(i < n)
    {
      res = res * a;
      i++;
    }
  return (res);
}
