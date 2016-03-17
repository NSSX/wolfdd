#include "my_h.h"

void parcour_all(t_struct *mystruct)
{
  int i;
  int j;
  int mypixelcolor;

  mypixelcolor = 0;
  j = 0;
  while(j < HEIGHT)
    {
      i = 0;
      while(i < WIDTH)
	{
          mypixelcolor = define_color(i, j, mystruct);
          if(mypixelcolor != 0)
            {
              my_pixel_put_to_image2(mystruct->img, i, j, mypixelcolor);
            }
          i++;
	}
      j++;
    }
}

