#include "ft_cube.h"
#include <math.h>
void vector_dir_value(t_parsing *pars)
{
	if (pars->pos_player == 'N')
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
	if (pars->pos_player == 'S')
	{
		pars->dirX = 1;
		pars->dirY = 0;
    pars->planeX = 0;
    pars->planeY = 0.66;
	}
	if (pars->pos_player == 'W')
	{
		pars->dirX = -1;
		pars->dirY = 0;
    pars->planeX = 0;
    pars->planeY = -0.66;
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

int             key_action(int keycode, t_parsing *pars)
{
  printf("posx :%f posy :%f dirx :%f diry :%f planex :%f planey :%f\n", pars->posX, pars->posY, pars->dirX, pars->dirY, pars->planeX, pars->planeY);
  printf("%d\n", keycode);
  if (keycode == 65307)
  {
        ft_putchar('d');
        mlx_destroy_window(pars->mlx, pars->win);
        ft_putchar('e');
        free_all(pars);
        exit(0);
  }
    if (keycode == 122)
    {
      if(pars->worldMap[(int)(pars->posX + pars->dirX * pars->moveSpeed)][(int)pars->posY] != '1')
        pars->posX += pars->dirX * pars->moveSpeed;
      if(pars->worldMap[(int)pars->posX][(int)(pars->posY + pars->dirY * pars->moveSpeed)] != '1')
        pars->posY += pars->dirY * pars->moveSpeed; 
    }
    if (keycode == 115)
    {
      if(pars->worldMap[(int)(pars->posX - pars->dirX * pars->moveSpeed)][(int)pars->posY] != '1')
        pars->posX -= pars->dirX * pars->moveSpeed;
      if(pars->worldMap[(int)pars->posX][(int)(pars->posY - pars->dirY * pars->moveSpeed)] != '1')
        pars->posY -= pars->dirY * pars->moveSpeed;
    }
    if (keycode == 100)
    {
      pars->oldDirX = pars->dirX;
      pars->dirX = pars->dirX * cos(pars->rotSpeed) - pars->dirY * sin(pars->rotSpeed);
      pars->dirY = pars->oldDirX * sin(pars->rotSpeed) + pars->dirY * cos(pars->rotSpeed);
      pars->oldPlaneX = pars->planeX;
      pars->planeX = pars->planeX * cos(pars->rotSpeed) - pars->planeY * sin(pars->rotSpeed);
      pars->planeY = pars->oldPlaneX * sin(pars->rotSpeed) + pars->planeY * cos(pars->rotSpeed);
    }
    if (keycode == 113)
    {
      pars->oldDirX = pars->dirX;
      pars->dirX = pars->dirX * cos(-pars->rotSpeed) - pars->dirY * sin(-pars->rotSpeed);
      pars->dirY = pars->oldDirX * sin(-pars->rotSpeed) + pars->dirY * cos(-pars->rotSpeed);
      pars->oldPlaneX = pars->planeX;
      pars->planeX = pars->planeX * cos(-pars->rotSpeed) - pars->planeY * sin(-pars->rotSpeed);
      pars->planeY = pars->oldPlaneX * sin(-pars->rotSpeed) + pars->planeY * cos(-pars->rotSpeed);
    }
    //printf("posx :%f posy :%f dirx :%f diry :%f planex :%f planey :%f\n", pars->posX, pars->posY, pars->dirX, pars->dirY, pars->planeX, pars->planeY);
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
		verif_argument_save(av[2]);
	recup_file(fd, &pars);

  vector_dir_value(&pars);

  pars.w = pars.res_x;
  pars.h = pars.res_y;
  pars.tex_line_lenght = pars.tex_wight * 4;
  pars.moveSpeed = 0.2;
  pars.rotSpeed = 0.1;
    pars.win = mlx_new_window(pars.mlx, pars.res_x, pars.res_y, "Cube3D");
    pars.img = mlx_new_image(pars.mlx, pars.res_x, pars.res_y);
    pars.addr = mlx_get_data_addr(pars.img, &pars.bits_per_pixel, &pars.line_length, &pars.endian);
	raycasting(&pars);
    mlx_hook(pars.win, 2, 1L<<0, key_action, &pars);
    mlx_loop(pars.mlx);
}
  
  
  void  raycasting(t_parsing *pars)
  {
    int x;
    x = 0;
   // int  buffer[pars->res_y][pars->res_x];
    clean_screen(pars, pars->res_x, pars->res_y);
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
      while(pars->drawStart <= pars->drawEnd)
      {
        int texY = (int)texPos;
        texPos += step;
		
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
       pars->alpha = pars->addr_no[pars->line_length_no * texY + texX * 4];
       pars->red = pars->addr_no[pars->line_length_no * texY + texX * 4 + 1];
       pars->green = pars->addr_no[pars->line_length_no * texY + texX * 4 + 2];
       pars->blue = pars->addr_no[pars->line_length_no * texY + texX * 4 + 3];
       // printf("tex height :%d\n", pars->tex_height);
	   //printf("%d %d\n", pars->drawStart, pars->drawEnd);
      
        //printf("color1 :%d\n", color);
        //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
        //if(pars->side == 1) color = (color >> 1) & 8355711;
       // printf("color2 :%d\n", color);
        //buffer[y][x] = color;
        my_mlx_pixel_put(pars, x, pars->drawStart, 255);
        pars->drawStart++;
      }
      x++;
    }
	printf("acualisation\n");
    mlx_put_image_to_window(pars->mlx, pars->win, pars->img, 0, 0);
  }