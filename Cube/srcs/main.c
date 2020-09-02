#include "ft_cube.h"
#include <math.h>
void vector_dir_value(t_parsing *pars)
{
  //printf("player %c\n", pars->pos_player);
	if (pars->pos_player == 'W')
	{
		pars->dirX = 0;
		pars->dirY = -1;
    pars->planeX = 0.66;
    pars->planeY = 0;
	}
	if (pars->pos_player == 'E')
	{
		pars->dirX = 0;
		pars->dirY = 1;
    pars->planeX = -0.66;
    pars->planeY = 0;
	}
	if (pars->pos_player == 'N')
	{
		pars->dirX = 1;
		pars->dirY = 0;
    pars->planeX = 0;
    pars->planeY = 0.66;
	}
	if (pars->pos_player == 'S')
	{
		pars->dirX = -1;
		pars->dirY = 0;
    pars->planeX = 0;
    pars->planeY = -0.66;
	}
}

char            *get_addr_tex(t_parsing *pars)
{
  if (pars->side == 0)
  {
    if(pars->rayDirX < 0)
      return(pars->addr_so);
    else
      return(pars->addr_no);
  }
  else
  {
    if (pars->rayDirY < 0)
      return(pars->addr_we);
    else
      return(pars->addr_ea);
  }
}

int             get_line_length_tex(t_parsing *pars)
{
  if (pars->side == 0)
  {
    if(pars->rayDirX < 0)
      return(pars->line_length_so);
    else
      return(pars->line_length_no);
  }
  else
  {
    if (pars->rayDirY < 0)
      return(pars->line_length_we);
    else
      return(pars->line_length_ea);
  }
}

void            decalage_bit(t_parsing *pars, int color)
{
    int copy;

    copy = color & 0xFF0000;
    pars->red = copy >> 16;
    copy = color & 0x00FF00;
    pars->green = copy >> 8;
    copy = color & 0xFF;
    pars->blue = color;
    copy = color & 0xFF000000;
    pars->alpha = color >> 24;
}

void            my_mlx_pixel_put(t_parsing *pars, int x, int y, int color)
{
    int pos;

    //printf("color :%d\n", color);
    pos = (x * 4 + y * pars->line_length);
    //decalage_bit(pars, color);
    if (color == 255)
    {
      pars->addr [pos + 0] = pars->alpha;
      pars->addr [pos + 1] = pars->red;
      pars->addr [pos + 2] = pars->green;
      pars->addr [pos + 3] = pars->blue;
    }
    else
    {
      pars->addr [pos + 0] = color;
      pars->addr [pos + 1] = color;
      pars->addr [pos + 2] = color;
      pars->addr [pos + 3] = color;
    }
}

void  raycasting_sprite(t_parsing *pars)
{
  int i;

  i = 0;
  while (i < pars->nb_sprite)
  {
      pars->sprite_order[i] = i;
      pars->sprite_dist[i] = ((pars->posX - pars->pos_sprite[i][0]) * (pars->posX - pars->pos_sprite[i][0]) 
      + (pars->posY - pars->pos_sprite[i][1]) * (pars->posY - pars->pos_sprite[i][1]));
      i++;
  }
    sort_sprites(pars);
    i = 0;
    while (i < pars->nb_sprite)
    {
      //printf("sprite x ;%d sprite y ;%d  nb sprite ;%d, sprite order :%d\n", pars->pos_sprite[pars->sprite_order[i]][0], pars->pos_sprite[pars->sprite_order[i]][1], pars->nb_sprite, pars->sprite_order[i]);
      double spriteX = pars->pos_sprite[pars->sprite_order[i]][0] + 0.5 - pars->posX;
      double spriteY = pars->pos_sprite[pars->sprite_order[i]][1] - pars->posY;
      double invDet = 1.0 / (pars->planeX * pars->dirY - pars->dirX * pars->planeY);

      double transformX = invDet * (pars->dirY * spriteX - pars->dirX * spriteY);
      double transformY = invDet * (-pars->planeY * spriteX + pars->planeX * spriteY);

      int spriteScreenX = (int)((pars->w / 2) * (1 + transformX / transformY));

      int spriteHeight = abs((int)(pars->h / (transformY)));
      int drawStartY = -spriteHeight / 2 + pars->h / 2;
      if(drawStartY < 0)
          drawStartY = 0;
      int drawEndY = spriteHeight / 2 + pars->h / 2;
      if(drawEndY >= pars->h)
        drawEndY = pars->h - 1;

      int spriteWidth = abs( (int) (pars->h / (transformY)));
      int drawStartX = -spriteWidth / 2 + spriteScreenX;
      if(drawStartX < 0)
          drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
      if(drawEndX >= pars->w)
        drawEndX = pars->w - 1;
      int stripe = drawStartX;
      while (stripe < drawEndX)
      {
        int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * pars->tex_wight / spriteWidth) / 256;
        //the conditions in the if are:
        //1) it's in front of camera plane so you don't see things behind you
        //2) it's on the screen (left)
        //3) it's on the screen (right)
        //4) ZBuffer, with perpendicular distance
        //printf("transformY ;%f stripe %d pars->w :%d z_buffer :%f\n", transformY, stripe, pars->w, pars->z_buffer[stripe]);
        if(transformY > 0 && stripe > 0 && stripe < pars->w && transformY < pars->z_buffer[stripe])
        {
            int y = drawStartY;
            while (y < drawEndY)
            {
              int d = (y) * 256 - pars->h * 128 + spriteHeight * 128;
              int texY = ((d * pars->tex_height) / spriteHeight) / 256;
              pars->alpha = pars->addr_s[pars->line_length_s * texY + texX * 4];
              pars->red = pars->addr_s[pars->line_length_s * texY + texX * 4 + 1];
              pars->green = pars->addr_s[pars->line_length_s * texY + texX * 4 + 2];
              pars->blue = pars->addr_s[pars->line_length_s * texY + texX * 4 + 3];
              if(!(pars->red == 0 && pars->blue == 0 && pars->green == 0))
                  my_mlx_pixel_put(pars, stripe, y, 255);
              y++;
            }
        }
        stripe++;
      }
      i++;
    }
}

void  color_ceiling(t_parsing *pars, int x)
{
  int i;

  i = 0;
  while (i < pars->drawStart)
  {
    //printf("rouge ;%d vert ;%d bleu ;%d\n", pars->r_ceil, pars->g_ceil, pars->b_ceil);
    pars->alpha = 0;
    pars->red = pars->r_ceil;
    pars->green = pars->g_ceil;
    pars->blue = pars->b_ceil;
    my_mlx_pixel_put(pars, x, i, 255);
    i++;
  }
}

void  color_floor(t_parsing *pars, int x)
{
  int i;

  i = pars->drawEnd + 1;
  while (i < pars->h)
  {
    pars->alpha = 0;
    pars->red = pars->r_floor;
    pars->green = pars->g_floor;
    pars->blue = pars->b_floor;
    my_mlx_pixel_put(pars, x, i, 255);
    i++;
  }
}

void  clean_screen(t_parsing *pars, int x_max, int y_max)
{
  int x;
  int y;

  y = 0;
  while (y < y_max)
  {
    x = 0;
    while (x < x_max)
    {
      my_mlx_pixel_put(pars, x, y, 0);
      x++;
    }
    y++;
  }
}


int             window_action(t_parsing *pars)
{
  mlx_destroy_window(pars->mlx, pars->win);
  free_all(pars);
  exit(0);
}

int             key_pressed(int keycode, t_parsing *pars)
{
  pars->key = keycode;
  return (0);
}

int             key_release(int keycode, t_parsing *pars)
{
  pars->key = 0;
  (void)keycode;
  return (0);
}

int             key_action(t_parsing *pars)
{
  if (pars->key == 65307)
  {
        mlx_destroy_window(pars->mlx, pars->win);
        free_all(pars);
        exit(0);
  }
  if (pars->key == 100)
  {
    if(pars->worldMap[(int)(pars->posX + pars->planeX * pars->moveSpeed)][(int)pars->posY] != '1')
        pars->posX += pars->planeX * pars->moveSpeed;
    if(pars->worldMap[(int)pars->posX][(int)(pars->posY + pars->planeY * pars->moveSpeed)] != '1')
        pars->posY += pars->planeY * pars->moveSpeed;
  }
  if (pars->key == 113)
  {
    if(pars->worldMap[(int)(pars->posX - pars->planeX * pars->moveSpeed)][(int)pars->posY] != '1')
        pars->posX -= pars->planeX * pars->moveSpeed;
    if(pars->worldMap[(int)pars->posX][(int)(pars->posY - pars->planeY * pars->moveSpeed)] != '1')
        pars->posY -= pars->planeY * pars->moveSpeed;
  }
    if (pars->key == 122)
    {
      if(pars->worldMap[(int)(pars->posX + pars->dirX * pars->moveSpeed)][(int)pars->posY] != '1')
        pars->posX += pars->dirX * pars->moveSpeed;
      if(pars->worldMap[(int)pars->posX][(int)(pars->posY + pars->dirY * pars->moveSpeed)] != '1')
        pars->posY += pars->dirY * pars->moveSpeed; 
    }
    if (pars->key == 115)
    {
      if(pars->worldMap[(int)(pars->posX - pars->dirX * pars->moveSpeed)][(int)pars->posY] != '1')
        pars->posX -= pars->dirX * pars->moveSpeed;
      if(pars->worldMap[(int)pars->posX][(int)(pars->posY - pars->dirY * pars->moveSpeed)] != '1')
        pars->posY -= pars->dirY * pars->moveSpeed;
    }
    if (pars->key == 65363)
    {
      pars->oldDirX = pars->dirX;
      pars->dirX = pars->dirX * cos(pars->rotSpeed) - pars->dirY * sin(pars->rotSpeed);
      pars->dirY = pars->oldDirX * sin(pars->rotSpeed) + pars->dirY * cos(pars->rotSpeed);
      pars->oldPlaneX = pars->planeX;
      pars->planeX = pars->planeX * cos(pars->rotSpeed) - pars->planeY * sin(pars->rotSpeed);
      pars->planeY = pars->oldPlaneX * sin(pars->rotSpeed) + pars->planeY * cos(pars->rotSpeed);
    }
    if (pars->key == 65361)
    {
      pars->oldDirX = pars->dirX;
      pars->dirX = pars->dirX * cos(-pars->rotSpeed) - pars->dirY * sin(-pars->rotSpeed);
      pars->dirY = pars->oldDirX * sin(-pars->rotSpeed) + pars->dirY * cos(-pars->rotSpeed);
      pars->oldPlaneX = pars->planeX;
      pars->planeX = pars->planeX * cos(-pars->rotSpeed) - pars->planeY * sin(-pars->rotSpeed);
      pars->planeY = pars->oldPlaneX * sin(-pars->rotSpeed) + pars->planeY * cos(-pars->rotSpeed);
    }
      raycasting(pars);
    return (0);
}

int	main(int ac, char **av)
{
	int fd;
	t_parsing pars;

  	pars.mlx = mlx_init();
    pars.tex_height = 64;
    pars.tex_wight = 64;
    intit_struct_pars(&pars);
	fd = open(av[1], O_RDONLY);
	if (ac == 1 || ac > 3)
		error_argument();
	verif_argument(av[1]);
	if (ac == 3)
  {
		verif_argument_save(av[2]);
    pars.save = 1;
  }
	recup_file(fd, &pars);
  close(fd);

  vector_dir_value(&pars);

  pars.w = pars.res_x;
  pars.h = pars.res_y;
  pars.z_buffer = malloc(sizeof(double) * pars.res_x + 1);
  pars.z_buffer[pars.res_x] = '\0';
  pars.moveSpeed = 0.2;
  pars.rotSpeed = 0.1;
    pars.win = mlx_new_window(pars.mlx, pars.res_x, pars.res_y, "Cube3D");
    pars.img = mlx_new_image(pars.mlx, pars.res_x, pars.res_y);
    pars.addr = mlx_get_data_addr(pars.img, &pars.bits_per_pixel, &pars.line_length, &pars.endian);
	  raycasting(&pars);
    mlx_loop_hook(pars.mlx, key_action, &pars);
    mlx_hook(pars.win, 2, 1L<<0, key_pressed, &pars);
    mlx_hook(pars.win, 3, 1L<<1, key_release, &pars);
    mlx_hook(pars.win, 33, 1L<<17, window_action, &pars);
    mlx_loop(pars.mlx);
}
  
  
  void  raycasting(t_parsing *pars)
  {
    int x;
    x = 0;
   // clean_screen(pars, pars->res_x, pars->res_y);
    while(x < pars->w)
    {
      pars->cameraX = (2 * x) / (double)pars->w - 1;
      pars->rayDirX = pars->dirX + pars->planeX * pars->cameraX;
      pars->rayDirY = pars->dirY + pars->planeY * pars->cameraX;
      pars->mapX = (int)pars->posX;
      pars->mapY = (int)pars->posY;
     // printf("raydir; %f\n", pars->rayDirX);
      pars->deltaDistX = fabs(1 / pars->rayDirX);
      pars->deltaDistY = fabs(1 / pars->rayDirY);

      pars->hit = 0;
      if(pars->rayDirX < 0)
      {
        pars->stepX = -1;
        pars->sideDistX = (pars->posX - pars->mapX) * pars->deltaDistX;
      }
      else
      {
        pars->stepX = 1;
        pars->sideDistX = (pars->mapX + 1.0 - pars->posX) * pars->deltaDistX;
      }
      if(pars->rayDirY < 0)
      {
        pars->stepY = -1;
        pars->sideDistY = (pars->posY - pars->mapY) * pars->deltaDistY;
      }
      else
      {
        pars->stepY = 1;
        pars->sideDistY = (pars->mapY + 1.0 - pars->posY) * pars->deltaDistY;
      }
      //ft_putchar('a');
     //  printf("sidedistx; %f\n", pars->sideDistX);
     // printf("sidedisty; %f\n", pars->sideDistY);
      while (pars->hit == 0)
      {
        if(pars->sideDistX < pars->sideDistY)
        {
        //  ft_putchar('b');
          pars->sideDistX += pars->deltaDistX;
          pars->mapX += pars->stepX;
         // printf("mapx; %d\n", pars->mapX);
          pars->side = 0;
        }
        else
        {
        //  ft_putchar('c');
          pars->sideDistY += pars->deltaDistY;
          pars->mapY += pars->stepY;
          pars->side = 1;
        }
       // printf("mapx; %d\n", pars->mapX);
        //printf("mapy; %d\n", pars->mapY);
        if(pars->worldMap[pars->mapX][pars->mapY] == '1')
          pars->hit = 1;
      }
      //printf("mapy; %d\n", pars->mapY);
     // printf("posy; %f\n", pars->posY);
     // printf("stepy; %d\n", pars->stepY);
     // printf("raydir; %f\n", pars->rayDirY);
     // printf("side; %d\n", pars->side);
      if(pars->side == 0)
        pars->perpWallDist = (pars->mapX - pars->posX + (1 - pars->stepX) / 2) / pars->rayDirX;
      else
        pars->perpWallDist = (pars->mapY - pars->posY + (1 - pars->stepY) / 2) / pars->rayDirY;

      pars->lineHeight = (int)(pars->h / pars->perpWallDist);
     // printf("wall dist; %g\n", pars->perpWallDist);
      pars->drawStart = -pars->lineHeight / 2 + pars->h / 2;
      if(pars->drawStart < 0)
        pars->drawStart = 0;
      pars->drawEnd = pars->lineHeight / 2 + pars->h / 2;
      if(pars->drawEnd >= pars->h)
        pars->drawEnd = pars->h - 1;


      //texturing calculations
      //int texNum = 1; //1 subtracted from it so that texture 0 can be used!

      //calculate value of wallX
      double wallX; //where exactly the wall was hit
      if (pars->side == 0)
	  	wallX = pars->posY + pars->perpWallDist * pars->rayDirY;
      else
	  	wallX = pars->posX + pars->perpWallDist * pars->rayDirX;

	wallX -= floor(wallX);
      //x coordinate on the texture
      int texX = (int)(wallX * (double)(pars->tex_wight));
      if(pars->side == 0 && pars->rayDirX > 0)
        texX = pars->tex_wight - texX - 1;
      if(pars->side == 1 && pars->rayDirY < 0)
        texX = pars->tex_wight - texX - 1;
      
            // How much to increase the texture coordinate per screen pixel
      double step = 1.0 *(double)pars->tex_height / (double)pars->lineHeight;
      // Starting texture coordinate
      double texPos = (double)(pars->drawStart - pars->h / 2 + pars->lineHeight / 2) * step;
      color_ceiling(pars, x);
      while(pars->drawStart <= pars->drawEnd)
      {
        int texY = (int)texPos;
        texPos += step;
        pars->addr_tex = get_addr_tex(pars);
        pars->line_length_tex = get_line_length_tex(pars);
       pars->alpha = pars->addr_tex[pars->line_length_tex * texY + texX * 4];
       pars->red = pars->addr_tex[pars->line_length_tex * texY + texX * 4 + 1];
       pars->green = pars->addr_tex[pars->line_length_tex * texY + texX * 4 + 2];
       pars->blue = pars->addr_tex[pars->line_length_tex * texY + texX * 4 + 3];
        my_mlx_pixel_put(pars, x, pars->drawStart, 255);
        pars->drawStart++;
      }
      color_floor(pars, x);
      pars->z_buffer[x] = pars->perpWallDist;
      x++;
    }
    raycasting_sprite(pars);
    mlx_put_image_to_window(pars->mlx, pars->win, pars->img, 0, 0);
    if (pars->save == 1)
    {
        make_bmp(pars);
        pars->save = 0;
    }
  }