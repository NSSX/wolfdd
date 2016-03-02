#include "wolf.h"

void line(t_img *myimg, float xi, float yi, float xf, float yf, int color);
void draw(t_struct *mystruct);

int worldMap[mapWidth][mapHeight]=
  {
    {8,8,8,8,8,8,9,9,9,9,3,9,9,9,9,9,8,8,8,8,8,8,8},
    {8,0,0,0,0,9,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,9,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,9,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,9,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,9,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,9,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,9,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,9,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,9,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,9,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,9,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,9,9,9,0,9,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,9,0,9,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,8,8,8,8,8,8,8,8,9,0,9,8,8,8,8,8,8,8,8,8,8,8,8},
    {8,0,0,0,0,0,0,0,0,9,0,9,0,0,0,0,0,0,0,0,0,0,4,8},
    {8,0,0,8,0,0,0,0,0,9,0,9,0,0,0,0,0,8,8,0,8,8,8,8},
    {8,0,0,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,8,0,8,8,8,8,8,8,8,8,8,8,8,0,0,0,0,8,8,0,8},
    {8,0,0,8,8,8,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,8},
    {8,0,0,8,0,8,0,8,8,8,0,8,8,8,0,8,0,0,0,8,0,0,0,8},
    {8,0,0,8,0,8,0,8,0,8,0,8,0,8,0,8,0,0,0,8,0,8,0,8},
    {8,0,0,0,8,8,0,8,0,8,0,8,0,8,0,8,0,0,0,8,0,8,0,8},
    {8,0,0,0,0,8,0,8,0,8,0,8,0,8,0,8,0,0,0,0,0,8,0,8},
    {8,0,8,8,0,0,0,8,0,8,0,8,0,8,0,8,0,0,0,0,8,0,8,8},
    {8,0,0,8,8,8,8,8,0,8,0,8,0,8,0,8,8,8,8,0,8,0,8,8},
    {8,0,0,8,0,0,0,0,0,8,0,8,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,8,0,8,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8}
  };

int             event_mlx(int keycode, t_struct *mystruct)
{
  double moveSpeed = 1;
  double rotSpeed = 0.1;
  
  if (keycode == 53)
    exit(1);
  if(keycode == 14)
    mystruct->eetat = 1;
  if(keycode == 12)
    mystruct->qetat = 1;
  if(keycode == 257)
     mystruct->shiftetat = 1;
  if(keycode == 126)
    mystruct->upetat = 1;
  if(keycode == 124)
    mystruct->rightetat = 1;
  if(keycode == 123)
    mystruct->leftetat = 1;
  if(keycode == 125)
    mystruct->downetat = 1;
  return (0);
}

void gotet(t_struct *mystruct)
{
  int i;
  i = 840;
  while(i < 890)
    {  
      line(mystruct->img, 840, i, 890, i, 0xFFFFFF);  
      i++;
    }
}

int ok_draw(int y1, int y2)
{
  if(y1 <= 0 || y1 >= HEIGHT || y2 <= 0 || y2 >= HEIGHT)
    return (0);
  return (1);
}

void draw(t_struct *mystruct)
{

 double posX = mystruct->wolf->posX;
 double posY = mystruct->wolf->posY;
 double dirX = mystruct->wolf->dirX; 
double dirY = mystruct->wolf->dirY; //initial direction vector

 double planeX = mystruct->wolf->planeX;
 double planeY = mystruct->wolf->planeY;

 double time = 0; //time of current frame
 double oldTime = 0; //time of previous frame

 
 for(int x = 0; x < WIDTH; x++)
   {
     //calculate ray position and direction
     double cameraX = 2 * x / (double)(WIDTH) - 1; //x-coordinate in camera space
     double rayPosX = posX;
     double rayPosY = posY;
     double rayDirX = dirX + planeX * cameraX;
     double rayDirY = dirY + planeY * cameraX;
     //which box of the map we're in
     int mapX = (int)rayPosX;
     int mapY = (int)rayPosY;

     //length of ray from current position to next x or y-side
     double sideDistX;
     double sideDistY;

     //length of ray from one x or y-side to next x or y-side
     double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
     double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
     double perpWallDist;

     //what direction to step in x or y-direction (either +1 or -1)
     int stepX;
     int stepY;

     int hit = 0; //was there a wall hit?
     int side; //was a NS or a EW wall hit?
     //calculate step and initial sideDist
     if (rayDirX < 0)
       {
	 stepX = -1;
	 sideDistX = (rayPosX - mapX) * deltaDistX;
       }
     else
       {
	 stepX = 1;
	 sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
       }
     if (rayDirY < 0)
       {
	 stepY = -1;
	 sideDistY = (rayPosY - mapY) * deltaDistY;
       }
     else
       {
	 stepY = 1;
	 sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
       }
     //perform DDA

     while (hit == 0)
       {
	 //jump to next map square, OR in x-direction, OR in y-direction
	 if (sideDistX < sideDistY)
	   {
	     sideDistX += deltaDistX;
	     mapX += stepX;
	     side = 0;
	   }
	 else
	   {
	     sideDistY += deltaDistY;
	     mapY += stepY;
	     side = 1;
	   }

	 //Check if ray has hit a wall
	 if (mystruct->worldMap[mapX][mapY] > 0) hit = 1;
       }
     //Calculate distance projected on camera direction (oblique distance will give fisheye effect!)
     if (side == 0) perpWallDist = (mapX - rayPosX + (1 - stepX) / 2) / rayDirX;
     else           perpWallDist = (mapY - rayPosY + (1 - stepY) / 2) / rayDirY;

     //Calculate height of line to draw on screen
     int lineHeight = (int)(HEIGHT / perpWallDist);

     //calculate lowest and highest pixel to fill in current stripe
     int drawStart = -lineHeight / 2 + HEIGHT / 2;
     if(drawStart < 0)drawStart = 0;//MAYBE CONDITION HERE
     int drawEnd = lineHeight / 2 + HEIGHT / 2;
     if(drawEnd >= HEIGHT)
       {
	 drawEnd = HEIGHT - 1;
       }
     else if(drawEnd <= 0)
       {
	 drawEnd = 1;
       }
     //choose wall color
     int color;
     switch(mystruct->worldMap[mapX][mapY])
       {
       case 1:  color = 0xFF0000;  break; //red
       case 2:  color = 0xFFFFFF;  break; //green
       case 3:  color = 0x0045FF;   break; //blue
       case 4:  color = 0xFFFFFF;  break; //white
       case 9: color = 0x000000; break;
       default: color = 0x00FFFF; break; //yellow
       }
     //give x and y sides different brightness
     if (side == 1) 
       color = color / 2;
     if(mystruct->worldMap[mapX][mapY] == 8)
       {
	 if(side == 0)
	   {
	     if(stepX < 0)
	       color = 0xFF0000;     
	     else
	       color = 0xFFFF00;
	   }
	 else
	   {
	     if(stepY < 0)
	       color = 0x0000FF;
	     else
	       color = 0x00FF00;
	   }
       }
     line(mystruct->img, x, 10, x, drawStart, 0x00F0F0);//sky
     line(mystruct->img, x, drawStart, x, drawEnd, color);//decor
     line(mystruct->img, x, drawEnd, x, HEIGHT - 2 , 0x0000FF / 3);//floor
   }
}



int the_move(t_struct *mystruct)
{
  static int possX;
  static int first;
  static int count;

  double moveSpeed = 0.1;
  double rotSpeed = 0.05;
  int poss;

  poss = 10;
  if(!count)
    {
      count = 0;
    }
  if(!first)
    {
      first = 5;
    }
  if(!possX)
    {
      possX = 0;
    }

  if(mystruct->eetat == 1 && mystruct->gotetat == 1)
    {
      mystruct->valuev = 5;	  
    }
  else if(mystruct->eetat == 0)
    mystruct->valuev = 1;
  count++;
  if(count >= mystruct->valuev)//Value pour le temps de rafrachissement
    {
      mystruct->worldMap[3][first - 1] = 0;
      mystruct->worldMap[3][first] = 2;
      if(mystruct->wolf->posX >= 3 && mystruct->wolf->posX <= 5 && mystruct->wolf->posY >= first - 1 && mystruct->wolf->posY <= first + 1)
	{
	  mystruct->wolf->posX = 11;
          mystruct->wolf->posY = 10;
	}
      if(first < 24)
	first++;
      else
	first = 5;
      count = 0;
    }

  if(mystruct->shiftetat  == 1)
    {
      moveSpeed = 0.4;
      rotSpeed = 0.2;
    }
  else if(mystruct->shiftetat  == 0)
    {
      moveSpeed = 0.1;
      rotSpeed = 0.05;
    }
  if(mystruct->upetat == 1)
    {
      if(mystruct->worldMap[(int)(mystruct->wolf->posX + mystruct->wolf->dirX * moveSpeed)][(int)mystruct->wolf->posY] == 0) mystruct->wolf->posX += mystruct->wolf->dirX * moveSpeed;
      if(mystruct->worldMap[(int)(mystruct->wolf->posX)][(int)(mystruct->wolf->posY + mystruct->wolf->dirY * moveSpeed)] == 0) mystruct->wolf->posY += mystruct->wolf->dirY * moveSpeed;
    }
  if(mystruct->downetat == 1)
    {
      if(mystruct->worldMap[(int)(mystruct->wolf->posX - mystruct->wolf->dirX * moveSpeed)][(int)mystruct->wolf->posY] == 0) mystruct->wolf->posX -= mystruct->wolf->dirX * moveSpeed;
      if(mystruct->worldMap[(int)(mystruct->wolf->posX)][(int)(mystruct->wolf->posY - mystruct->wolf->dirY * moveSpeed)] == 0) mystruct->wolf->posY -= mystruct->wolf->dirY * moveSpeed;
    }

  if(mystruct->leftetat == 1)
    {
      double oldDirX = mystruct->wolf->dirX;
      mystruct->wolf->dirX = mystruct->wolf->dirX * cos(rotSpeed) - mystruct->wolf->dirY * sin(rotSpeed);
      mystruct->wolf->dirY = oldDirX * sin(rotSpeed) + mystruct->wolf->dirY * cos(rotSpeed);
      double oldPlaneX = mystruct->wolf->planeX;
      mystruct->wolf->planeX = mystruct->wolf->planeX * cos(rotSpeed) - mystruct->wolf->planeY * sin(rotSpeed);
      mystruct->wolf->planeY = oldPlaneX * sin(rotSpeed) + mystruct->wolf->planeY * cos(rotSpeed);
    }

  if(mystruct->rightetat == 1)
    {
      double oldDirX = mystruct->wolf->dirX;
      mystruct->wolf->dirX = mystruct->wolf->dirX * cos(-rotSpeed) - mystruct->wolf->dirY * sin(-rotSpeed);
      mystruct->wolf->dirY = oldDirX * sin(-rotSpeed) + mystruct->wolf->dirY * cos(-rotSpeed);
      double oldPlaneX = mystruct->wolf->planeX;
      mystruct->wolf->planeX = mystruct->wolf->planeX * cos(-rotSpeed) - mystruct->wolf->planeY * sin(-rotSpeed);
      mystruct->wolf->planeY = oldPlaneX * sin(-rotSpeed) + mystruct->wolf->planeY * cos(-rotSpeed);
    }

    if(mystruct->qetat == 1)
      {
	if(mystruct->wolf->posX >= 15 && mystruct->wolf->posX <= 16 && mystruct->wolf->posY >= 21 && mystruct->wolf->posY <= 22.5)
	  {
	    mystruct->worldMap[15][22] = 0;
	    mystruct->gotetat = 1; 
	  }
	if(mystruct->wolf->posX >= 0.8 && mystruct->wolf->posX <= 1.5 && mystruct->wolf->posY >= 10 && mystruct->wolf->posY <= 11)
          {
	    printf("Merci de bien noter c'etais jolie\n");
	    exit(1);
          }
      }
      mlx_destroy_image(mystruct->mlx, mystruct->img->img_ptr);
      mystruct->img->img_ptr = mlx_new_image(mystruct->mlx, WIDTH, HEIGHT);
      draw(mystruct);
      if(mystruct->gotetat == 1)
	{
	  gotet(mystruct);
	}
      mlx_put_image_to_window(mystruct->mlx, mystruct->win, mystruct->img->img_ptr, 0, 0);
  return (0);
}

int event_release(int keycode, t_struct *mystruct)
{
  if(keycode == 14)
      mystruct->eetat = 0;
  if(keycode == 12)
      mystruct->qetat = 0;
  if(keycode == 257)
      mystruct->shiftetat = 0;
  if(keycode == 126)
      mystruct->upetat = 0;
  if(keycode == 125)
      mystruct->downetat = 0;
  if(keycode == 123)
      mystruct->leftetat = 0;
  if(keycode == 124)
      mystruct->rightetat = 0;
  return (0);
}


void line(t_img *myimg, float xi, float yi, float xf, float yf, int color)
{
  int dx,dy,i,xinc,yinc,cumul,x,y ;
  x = xi ;
  y = yi ;
  dx = xf - xi ;
  dy = yf - yi ;
  xinc = ( dx > 0 ) ? 1 : -1 ;
  yinc = ( dy > 0 ) ? 1 : -1 ;
  dx = abs(dx) ;
  dy = abs(dy) ;
  //  if(ok_draw(yi,yf))
    my_pixel_put_to_image(myimg, x, y, color);
  if ( dx > dy ) {
    cumul = dx / 2 ;
    for ( i = 1 ; i <= dx ; i++ ) {
      x += xinc ;
      cumul += dy ;
      if ( cumul >= dx ) {
	cumul -= dx ;
	y += yinc ; }
      // if(ok_draw(yi,yf))
       my_pixel_put_to_image(myimg, x, y, color); } }
  else {
    cumul = dy / 2 ;
    for ( i = 1 ; i <= dy ; i++ ) {
      y += yinc ;
      cumul += dx ;
      if ( cumul >= dy ) {
	cumul -= dy ;
	x += xinc ; }
      // if(ok_draw(yi,yf))
	my_pixel_put_to_image(myimg, x, y, color); } }
}

int main(void)
{
  t_struct *mystruct;

  mystruct = give_struct();


int world[12][mapHeight]=
  {
    {8,8,8,8,8,8,9,9,9,9,3,9,9,9,9,9,8,8,8,8,8,8,8},
    {8,0,0,0,0,9,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,9,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,9,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,9,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,9,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,9,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,9,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,9,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,9,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,9,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,9,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,8},
  };

int world2[17][mapHeight] =
  {
    {8,0,0,0,0,0,0,9,9,9,0,9,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,9,0,9,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,8,8,8,8,8,8,8,8,9,0,9,8,8,8,8,8,8,8,8,8,8,8,8},
    {8,0,0,0,0,0,0,0,0,9,0,9,0,0,0,0,0,0,0,0,0,0,4,8},
    {8,0,0,8,0,0,0,0,0,9,0,9,0,0,0,0,0,8,8,0,8,8,8,8},
    {8,0,0,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,8,0,8,8,8,8,8,8,8,8,8,8,8,0,0,0,0,8,8,0,8},
    {8,0,0,8,8,8,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,8},
    {8,0,0,8,0,8,0,8,8,8,0,8,8,8,0,8,0,0,0,8,0,0,0,8},
    {8,0,0,8,0,8,0,8,0,8,0,8,0,8,0,8,0,0,0,8,0,8,0,8},
    {8,0,0,0,8,8,0,8,0,8,0,8,0,8,0,8,0,0,0,8,0,8,0,8},
    {8,0,0,0,0,8,0,8,0,8,0,8,0,8,0,8,0,0,0,0,0,8,0,8},
    {8,0,8,8,0,0,0,8,0,8,0,8,0,8,0,8,0,0,0,0,8,0,8,8},
    {8,0,0,8,8,8,8,8,0,8,0,8,0,8,0,8,8,8,8,0,8,0,8,8},
    {8,0,0,8,0,0,0,0,0,8,0,8,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,8,0,8,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8}
  };

 int i = 0;
 int j = 0;
 while(i < 12)
   {
     j = 0;
     while(j < mapHeight)
       {
	 mystruct->worldMap[i][j] = world[i][j];
	 j++;
       }
     i++;
   }
 int i2;
 i2 = 0;
 while(i < 29)
   {
     j = 0;
     while(j < mapHeight)
       {
         mystruct->worldMap[i][j] = world2[i2][j];
         j++;
       }
     i2++;
     i++;
   }

  //Start Wolf
  draw(mystruct);
  //End wolf
  mlx_key_hook(mystruct->win, event_release, mystruct);
  mlx_hook(mystruct->win, 2, (1L<<1), event_mlx, mystruct);
  mlx_put_image_to_window(mystruct->mlx, mystruct->win, mystruct->img->img_ptr, 0, 0);
  mlx_loop_hook (mystruct->mlx, the_move, mystruct);
  mlx_loop(mystruct->mlx);
  return (0);
}
