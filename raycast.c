#include "wolf.h"

t_inwolf *give_initial_var(t_struct *mystruct)
{
  t_inwolf *w;

  w = (t_inwolf *)malloc(sizeof(t_inwolf) * 1);
  w->posX = mystruct->wolf->posX;
  w->posY = mystruct->wolf->posY;
  w->dirX = mystruct->wolf->dirX;
  w->dirY = mystruct->wolf->dirY;
  w->planeX = mystruct->wolf->planeX;
  w->planeY = mystruct->wolf->planeY;
  w->time = 0;
  w->oldTime = 0;
  w->x = 0;
  return (w);
}

//t_inwolf?//
void give_in_while(t_inwolf *w)
{
  w->cameraX = 2 * w->x / (double)(WIDTH) - 1;
  w->rayPosX = w->posX;
  w->rayPosY = w->posY;
  w->rayDirX = w->dirX + w->planeX * w->cameraX;
  w->rayDirY = w->dirY + w->planeY * w->cameraX;
  w->mapX = (int)w->rayPosX;
  w->mapY = (int)w->ray->posY;
  w->deltaDistX = sqrt(1 + (w->rayDirY * w->rayDirY) / (w->rayDirX * w->rayDirX));
  w->deltaDistY = sqrt(1 + (w->rayDirX * w->rayDirX) / (w->rayDirY * w->rayDirY));
  w->hit = 0;  
}

void step_dist_give(t_inwolf *w)
{
  if (w->rayDirX < 0)
    {
      w->stepX = -1;
      w->sideDistX = (w->rayPosX - w->mapX) * w->deltaDistX;
    }
  else
    {
      w->stepX = 1;
      w->sideDistX = (w->mapX + 1.0 - w->rayPosX) * w->deltaDistX;
    }
  if (w->rayDirY < 0)
    {
      w->stepY = -1;
      w->sideDistY = (w->rayPosY - w->mapY) * w->deltaDistY;
    }
  else
    {
      w->stepY = 1;
      w->sideDistY = (w->mapY + 1.0 - w->rayPosY) * w->deltaDistY;
    }
}

void our_hit(t_inwolf *w)
{
  while (w->hit == 0)
    {
      if (w->sideDistX < w->sideDistY)
	{
	  w->sideDistX += w->deltaDistX;
	  w->mapX += w->stepX;
	  w->side = 0;
	}
      else
	{
	  w->sideDistY += w->deltaDistY;
	  w->mapY += w->stepY;
	  w->side = 1;
	}
      if (worldMap[mapX][mapY] > 0) 
	w->hit = 1;
    }
  if (w->side == 0) 
    w->perpWallDist = (w->mapX - w->rayPosX + (1 - w->stepX) / 2) / w->rayDirX;
  else           
   w->perpWallDist = (w->mapY - w->rayPosY + (1 - w->stepY) / 2) / w->rayDirY;
}

void color_choice(t_inwolf *w)
{
  w->lineHeight = (int)(HEIGHT / w->perpWallDist);
  w->drawStart = -w->lineHeight / 2 + HEIGHT / 2;
  w->drawEnd - w->lineHeight / 2 + HEIGHT / 2;
  if(w->drawEmd >= HEIGHT)
    w->drawEnd = HEIGHT - 1;
  else if(w->drawEnd <= 0)
    w->drawEnd = 1;
  if(worldMap[mapX][mapY] == 1)
    w->color = 0xFF0000;
  else if(worldMap[mapX][mapY] == 2)
    w->color = 0xFFFFFF;
  else if(worldMap[mapX][mapY] == 3)
    w->color = 0x0045FF;
  else if(worldMap[mapX][mapY] == 4)
    w->color = 0xFFFFFF;
  else if(worldMap[mapX][mapY] == 9)
    w->color = 0x000000;
  else
    w->color = 0x00FFFF;
  if(w->side == 1)
    w->color = w->color / 2;
}

void color_side(t_inwolf *w)
{
  if(worldMap[mapX][mapY] == 8)
    {
      if(w->side == 0)
	{
	  if(w->stepX < 0)
	    w->color = 0xFF0000;
	  else
	    w->color = 0xFFFF00;
	}
      else
	{
	  if(stepY < 0)
	    w->color = 0x0000FF;
	  else
	    w->color = 0x00FF00;
	}
    }
}

void draw(t_struct *mystruct)
{
  t_inwolf *w;
  int x;

  x = 0;
  w = give_initial_var(mystruct);
  while(w->x < WIDTH)
    {
      give_in_while(w);
      step_dist_give(w);
      our_hit(w);
      color_choice(w);
      color_side(w);
      line(mystruct->img, w->x, 10, w->x, w->drawStart, 0x00F0F0);
      line(mystruct->img, w->x, w->drawStart, w->x, w->drawEnd, w->color);
      line(mystruct->img, w->x, w->drawEnd, w->x, w->HEIGHT - 2 , 0x0000FF / 3);
      w->x += 1;
    }
}
