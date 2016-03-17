#include "my_h.h"

void            my_shadow_sph(t_point *point, t_coord *sph, float k);
int             my_light_sph(t_point *point, t_struct *mystruct);
int             my_light_cone(t_point *point, t_struct *mystruct);
int             my_light_cyl(t_point *point, t_struct *mystruct);


int             calc_shadow_sph(t_point *point, t_coord *sph, float k)
{
  double a;
  double b;
  double c;
  double det;
  double myv1;
  double myv2;

  my_shadow_sph(point, sph, k);
  a = (pow(point->lum->vx, 2) + pow(point->lum->vy, 2) + pow(point->lum->vz, 2));
  b = 2 * (point->lum->vx * point->pos->xp + point->lum->vy * point->pos->yp
           + point->lum->vz * point->pos->zp);
  c = (pow(point->pos->xp, 2) + pow(point->pos->yp, 2)
       + pow(point->pos->zp, 2) - pow(sph->rayon, 2));
  det = (b * b) - (4 * a * c);
  if(det < 0)
    return (1);
  myv1 = (-b - sqrt(det)) / (2 * a);
  myv2 = (-b + sqrt(det)) / (2 * a);
  if(myv1 > myv2 && myv2 > 0)
    {
      myv1 = myv2;
    }
  if(myv1 > 0 && myv1 < 1)
    return (2);
  return (1);

}


void            my_value(t_point *point, int x, int y)
{
  point->lum->nx = 0;
  point->lum->ny = 0;
  point->lum->nz = 100;
  point->lum->x = -3000;
  point->lum->y = 0;
  point->lum->z = 2000;
  point->coord->vx = 0;
  point->coord->vy = (WIDTH / 2) - x;
  point->coord->vz = (HEIGHT / 2) - y;
  point->coord->xeye = -3000;
  point->coord->yeye = 0;
  point->coord->zeye = 500;
  point->sph->vx = point->coord->vx + 1000- 400;
  point->sph->vy = point->coord->vy + 0;
  point->sph->vz = point->coord->vz + -300;
  point->sph->rayon = 800;
  point->cyl->vx = point->coord->vx + 1000;
  point->cyl->vy = point->coord->vy + 0 - 100;
  point->cyl->vz = point->coord->vz + -300;
  point->cyl->rayon = 150;
  point->cone->vx = point->coord->vx + 1000;
  point->cone->vy = point->coord->vy + 0 + 100;
  point->cone->vz = point->coord->vz + -300;
}


int lets_choice(t_sphere *sphere, t_vec3d *plan, t_light *light, t_ray *ray, t_struct *mystruct, t_sphere *cone, t_sphere *cyl, t_point *point)
{
   double v;
  double v_value[4];
  int i;
  double temp;


  v = 0;
  i = -1;
  give_v(plan, sphere, cone, cyl, v_value, point);
  while(i < 2)
    {
      i++;
      if(v_value[i] > v_value[i + 1])
        {
          temp = v_value[i];
          v_value[i] = v_value[i + 1];
          v_value[i + 1] = temp;
          i = -1;
        }
    }
  i = 0;
  while(i < 4 && v_value[i] <= 0)
    {
      i++;
      if(i == 4)
	break;
    }
  if(v > 3)
    v = v_value[3];
  else
    v = v_value[i];
  give_v(mystruct->plan, sphere, cone, cyl, v_value, point);
  if(v == v_value[0])
    return (light_plan(point, mystruct));
  else if(v == v_value[1])
       return(my_light_cone(point, mystruct));
  else if(v == v_value[2])
    return(my_light_cyl(point, mystruct));
  else if(v == v_value[3])
    return(my_light_sph(point, mystruct));
  return (0x000000);
}

int define_color(int x, int y, t_struct *mystruct)
{
  int color;
  t_sphere *sphere;
  t_vec3d *plan;
  t_ray *ray;
  t_light *light;
  t_sphere *cone;
  t_sphere *cyl;
  t_point *point;

  point = (t_point *)malloc(sizeof(t_point) * 1);
  light = (t_light *)malloc(sizeof(t_light) * 1);
  ray = (t_ray *)malloc(sizeof(t_ray) * 1);
  ray->o = (t_vec3d *)malloc(sizeof(t_vec3d) * 1);
  ray->d = (t_vec3d *)malloc(sizeof(t_vec3d) * 1);
  plan = (t_vec3d *)malloc(sizeof(t_vec3d) * 1);
  cone = (t_sphere *)malloc(sizeof(t_sphere) * 1);
  cone->pos = (t_vec3d *)malloc(sizeof(t_vec3d) * 1);
  sphere = (t_sphere *)malloc(sizeof(t_sphere) * 1);
  sphere->pos = (t_vec3d *)malloc(sizeof(t_vec3d) * 1);
  cyl = (t_sphere *)malloc(sizeof(t_sphere) * 1);
  cyl->pos = (t_vec3d *)malloc(sizeof(t_vec3d) * 1);
  point->img = (t_img *)malloc(sizeof(t_img) * 1);
  point->coord = (t_coord *)malloc(sizeof(t_coord) * 1);
  point->sph = (t_coord *)malloc(sizeof(t_coord) * 1);
  point->cyl = (t_coord *)malloc(sizeof(t_coord) * 1);
  point->cone = (t_coord *)malloc(sizeof(t_coord) * 1);
  point->pos = (t_pos *)malloc(sizeof(t_pos) * 1);
  point->lum = (t_lum *)malloc(sizeof(t_lum) * 1);
  mystruct->plan = plan;
  mystruct->rays = ray;
  mystruct->spheres = sphere;
  mystruct->cones = cone;
  mystruct->cyls = cyl;
  mystruct->lights = light;
  color = 0;
  give_value(x, y,sphere, ray, mystruct->lights, mystruct, cone, cyl);
  my_value(point,x,y);
  plan_int(mystruct);  
  sphere_int(mystruct->spheres, ray);
  cone_int(mystruct->cones, ray);
  cyl_int(mystruct->cyls,ray);
  color = lets_choice(sphere, plan,mystruct->lights, ray, mystruct, cone, cyl, point);
  return (color);
}

int                     main(int argc, char **argv)
{
  t_struct *mystruct;
  t_img *myimg;

  mystruct = (t_struct *)malloc(sizeof(t_struct));
  myimg = (t_img *)malloc(sizeof(t_img));
  mystruct->mlx = mlx_init();
  mystruct->win = mlx_new_window(mystruct->mlx, WIDTH, HEIGHT, "RayTracer V1");
  myimg->img_ptr = mlx_new_image(mystruct->mlx, WIDTH, HEIGHT);
  mystruct->img = myimg;
  mystruct->decx = 1000;
  mystruct->decy = 0;
  mystruct->decz = -300;
  parcour_all(mystruct);
  mlx_put_image_to_window(mystruct->mlx, mystruct->win, mystruct->img->img_ptr, 0, 0);
  mlx_key_hook(mystruct->win, event_mlx, mystruct);
  mlx_loop(mystruct->mlx);
  return (0);
}
