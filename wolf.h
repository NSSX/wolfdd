#ifndef WOLF_H
#define WOLF_H
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
# define WIDTH 900
# define HEIGHT 900
#define mapWidth 29
#define mapHeight 24


typedef struct s_wolf
{
  double cameraX;
  double rayPosX;
  double rayPosY;
  double rayDirX;
  double rayDirY;
  double posX, posY;  //x and y start position
  double dirX, dirY; //initial direction vector
  double planeX, planeY; //the 2d raycaster version of camera plane
  double time; //time of current frame
  double oldTime; //time

}t_wolf;

typedef struct s_inwolf
{
  double posX;
  double posY;
  double dirX;
  double dirY;
  double planeX;
  double planeY;
  double time;
  double oldTime;
  double cameraX;
  double rayPosX;
  double rayPosY;
  double rayDirX;
  double rayDirY;
  int mapX;
  int mapY;
  double sideDistX;
  double sideDistY;
  double deltaDistX;
  double deltaDistY;
  double perpWallDist;
  int stepX;
  int stepY;
  int hit;
  int side;
  int lineHeight;
  int drawStart;
  int drawEnd;
  int color;
  int x;
}		t_inwolf;

typedef struct                                                  s_img
{
  void                    *mlx;
  void                    *win;
  unsigned long   img_color;
  char                    *data;
  void                    *img_ptr;
  int                             sizeline;
  int                             bpp;
  int                             x;
  int                             y;
  int                             endian;
  void                    *mlx_ptr;
}                                                                               t_img;

typedef struct                                                  s_line
{
  int dx;
  int dy;
  int i;
  int xinc;
  int yinc;
  int cumul;
  int x;
  int y;
}                                                                               t_line;

typedef struct                                                  s_temp
{
  int x1;
  int x2;
  int y1;
  int y2;
  int val1;
  int val2;
  int color;
}                                                                               t_temp;

typedef struct s_struct
{
  int qetat;
  int eetat;
  int shiftetat;
  int rightetat;
  int leftetat;
  int upetat;
  int downetat;
  int gotetat;
  int valuev;
  void *mlx;
  void *win;
  t_img                   *img;
  t_wolf *wolf;
  int worldMap[mapWidth][mapHeight];
  int i;
  int j;
  int i2;
}               t_struct;

t_struct *give_struct(void);
void    my_pixel_put_to_image(t_img *myimg, int x, int y, int color);
#endif
