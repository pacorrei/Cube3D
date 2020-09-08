/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2020/04/26 11:03:38 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

void	vector_dir_value2(t_parsing *pars)
{
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

void	vector_dir_value(t_parsing *pars)
{
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
	vector_dir_value2(pars);
}

char	*get_addr_tex(t_parsing *pars)
{
	if (pars->side == 0)
	{
		if (pars->rayDirX < 0)
			return (pars->addr_so);
		else
			return (pars->addr_no);
	}
	else
	{
		if (pars->rayDirY < 0)
			return (pars->addr_we);
		else
			return (pars->addr_ea);
	}
}

int		get_line_length_tex(t_parsing *pars)
{
	if (pars->side == 0)
	{
		if (pars->rayDirX < 0)
			return (pars->line_length_so);
		else
			return (pars->line_length_no);
	}
	else
	{
		if (pars->rayDirY < 0)
			return (pars->line_length_we);
		else
			return (pars->line_length_ea);
	}
}

void	my_mlx_pixel_put(t_parsing *pars, int x, int y, int color)
{
	int pos;

	pos = (x * 4 + y * pars->line_length);
	if (color == 255)
	{
		pars->addr[pos + 0] = pars->alpha;
		pars->addr[pos + 1] = pars->red;
		pars->addr[pos + 2] = pars->green;
		pars->addr[pos + 3] = pars->blue;
	}
	else
	{
		pars->addr[pos + 0] = color;
		pars->addr[pos + 1] = color;
		pars->addr[pos + 2] = color;
		pars->addr[pos + 3] = color;
	}
}

void	draw_sprite_value(t_parsing *pars)
{
	if (pars->spri_drawStartY < 0)
		pars->spri_drawStartY = 0;
	pars->spri_drawEndY = pars->spriteHeight / 2 + pars->h / 2;
	if (pars->spri_drawEndY >= pars->h)
		pars->spri_drawEndY = pars->h - 1;
	pars->spriteWidth = abs((int)(pars->h / (pars->transformY)));
	pars->spri_drawStartX = -pars->spriteWidth / 2 + pars->spriteScreenX;
	if (pars->spri_drawStartX < 0)
		pars->spri_drawStartX = 0;
	pars->spri_drawEndX = pars->spriteWidth / 2 + pars->spriteScreenX;
	if (pars->spri_drawEndX >= pars->w)
		pars->spri_drawEndX = pars->w - 1;
	pars->stripe = pars->spri_drawStartX;
}

void	initializes_sprite_value(t_parsing *pars, int i)
{
	pars->spriteX = pars->pos_sprite[pars->sprite_order[i]][0]
	+ 0.5 - pars->posX;
	pars->spriteY = pars->pos_sprite[pars->sprite_order[i]][1]
	+ 0.5 - pars->posY;
	pars->invDet = 1.0 / (pars->planeX * pars->dirY -
	pars->dirX * pars->planeY);
	pars->transformX = pars->invDet * (pars->dirY *
	pars->spriteX - pars->dirX * pars->spriteY);
	pars->transformY = pars->invDet * (-pars->planeY *
	pars->spriteX + pars->planeX * pars->spriteY);
	pars->spriteScreenX = (int)((pars->w / 2) * (1 +
	pars->transformX / pars->transformY));
	pars->spriteHeight = abs((int)(pars->h / (pars->transformY)));
	pars->spri_drawStartY = -pars->spriteHeight / 2 + pars->h / 2;
}

int		draw_sprite(t_parsing *pars, int y)
{
	int d;

	d = (y) * 256 - pars->h * 128 +
	pars->spriteHeight * 128;
	pars->spri_texY = ((d * pars->tex_height) /
	pars->spriteHeight) / 256;
	pars->alpha = pars->addr_s[pars->line_length_s *
	pars->spri_texY + pars->spri_texX * 4];
	pars->red = pars->addr_s[pars->line_length_s *
	pars->spri_texY + pars->spri_texX * 4 + 1];
	pars->green = pars->addr_s[pars->line_length_s *
	pars->spri_texY + pars->spri_texX * 4 + 2];
	pars->blue = pars->addr_s[pars->line_length_s *
	pars->spri_texY + pars->spri_texX * 4 + 3];
	if (!(pars->red == 0 && pars->blue == 0 && pars->green == 0))
		my_mlx_pixel_put(pars, pars->stripe, y, 255);
	y++;
	return (y);
}

void	verif_sprites_on_screen(t_parsing *pars)
{
	int y;

	pars->spri_texX = (int)(256 * (pars->stripe -
	(-pars->spriteWidth / 2 + pars->spriteScreenX)) *
	pars->tex_wight / pars->spriteWidth) / 256;
	if (pars->transformY > 0 && pars->stripe > 0 &&
	pars->stripe < pars->w && pars->transformY <
	pars->z_buffer[pars->stripe])
	{
		y = pars->spri_drawStartY;
		while (y < pars->spri_drawEndY)
			y = draw_sprite(pars, y);
	}
	pars->stripe++;
}

void	raycasting_sprite(t_parsing *pars)
{
	int i;

	i = 0;
	while (i < pars->nb_sprite)
	{
		pars->sprite_order[i] = i;
		pars->sprite_dist[i] = ((pars->posX - pars->pos_sprite[i][0]) *
		(pars->posX - pars->pos_sprite[i][0])
		+ (pars->posY - pars->pos_sprite[i][1]) *
		(pars->posY - pars->pos_sprite[i][1]));
		i++;
	}
	sort_sprites(pars);
	i = 0;
	while (i < pars->nb_sprite)
	{
		initializes_sprite_value(pars, i);
		draw_sprite_value(pars);
		while (pars->stripe < pars->spri_drawEndX)
			verif_sprites_on_screen(pars);
		i++;
	}
}

void	color_ceiling(t_parsing *pars, int x)
{
	int i;

	i = 0;
	while (i < pars->drawStart)
	{
		pars->alpha = 0;
		pars->red = pars->r_ceil;
		pars->green = pars->g_ceil;
		pars->blue = pars->b_ceil;
		my_mlx_pixel_put(pars, x, i, 255);
		i++;
	}
}

void	color_floor(t_parsing *pars, int x)
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

int		window_action(t_parsing *pars)
{
	mlx_destroy_window(pars->mlx, pars->win);
	free_all(pars);
	exit(0);
}

int		key_pressed(int keycode, t_parsing *pars)
{
	if (keycode == 100)
		pars->key_d = 1;
	if (keycode == 113)
		pars->key_q = 1;
	if (keycode == 122)
		pars->key_z = 1;
	if (keycode == 115)
		pars->key_s = 1;
	if (keycode == 65363)
		pars->key_right = 1;
	if (keycode == 65361)
		pars->key_left = 1;
	if (keycode == 65307)
		pars->key_echap = 1;
	mlx_put_image_to_window(pars->mlx, pars->win, pars->img, 0, 0);
	return (0);
}

int		key_release(int keycode, t_parsing *pars)
{
	pars->key_z = 0;
	pars->key_q = 0;
	pars->key_s = 0;
	pars->key_d = 0;
	pars->key_right = 0;
	pars->key_left = 0;
	pars->key_echap = 0;
	(void)keycode;
	mlx_put_image_to_window(pars->mlx, pars->win, pars->img, 0, 0);
	return (0);
}

int		main(int ac, char **av)
{
	int			fd;
	t_parsing	pars;

	pars.mlx = mlx_init();
	pars.tex_height = 64;
	pars.tex_wight = 64;
	intit_struct_pars(&pars);
	main_verif_argument(&pars, av, ac);
	fd = open(av[1], O_RDONLY);
	recup_file(fd, &pars);
	close(fd);
	vector_dir_value(&pars);
	pars.z_buffer = malloc(sizeof(double) * pars.res_x + 1);
	pars.z_buffer[pars.res_x] = '\0';
	pars.win = mlx_new_window(pars.mlx, pars.res_x, pars.res_y, "Cube3D");
	pars.img = mlx_new_image(pars.mlx, pars.res_x, pars.res_y);
	pars.addr = mlx_get_data_addr(pars.img, &pars.bits_per_pixel,
	&pars.line_length, &pars.endian);
	raycasting(&pars);
	mlx_loop_hook(pars.mlx, key_action, &pars);
	mlx_hook(pars.win, 2, 1L << 0, key_pressed, &pars);
	mlx_hook(pars.win, 3, 1L << 1, key_release, &pars);
	mlx_hook(pars.win, 33, 1L << 17, window_action, &pars);
	mlx_loop(pars.mlx);
}

void	draw_wall(t_parsing *pars, int x)
{
	pars->texY = (int)pars->texPos;
	pars->texPos += pars->step;
	pars->addr_tex = get_addr_tex(pars);
	pars->line_length_tex = get_line_length_tex(pars);
	pars->alpha = pars->addr_tex[pars->line_length_tex * pars->texY +
	pars->texX * 4];
	pars->red = pars->addr_tex[pars->line_length_tex * pars->texY +
	pars->texX * 4 + 1];
	pars->green = pars->addr_tex[pars->line_length_tex * pars->texY +
	pars->texX * 4 + 2];
	pars->blue = pars->addr_tex[pars->line_length_tex * pars->texY +
	pars->texX * 4 + 3];
	my_mlx_pixel_put(pars, x, pars->drawStart, 255);
	pars->drawStart++;
}

void	initializes_raycasting_value(t_parsing *pars, int x)
{
	pars->w = pars->res_x;
	pars->h = pars->res_y;
	pars->moveSpeed = 0.2;
	pars->rotSpeed = 0.1;
	pars->cameraX = (2 * x) / (double)pars->w - 1;
	pars->rayDirX = pars->dirX + pars->planeX * pars->cameraX;
	pars->rayDirY = pars->dirY + pars->planeY * pars->cameraX;
	pars->mapX = (int)pars->posX;
	pars->mapY = (int)pars->posY;
	pars->deltaDistX = fabs(1 / pars->rayDirX);
	pars->deltaDistY = fabs(1 / pars->rayDirY);
	pars->hit = 0;
}

void	side_value(t_parsing *pars)
{
	if (pars->rayDirX < 0)
	{
		pars->stepX = -1;
		pars->sideDistX = (pars->posX - pars->mapX) * pars->deltaDistX;
	}
	else
	{
		pars->stepX = 1;
		pars->sideDistX = (pars->mapX + 1.0 - pars->posX) *
		pars->deltaDistX;
	}
	if (pars->rayDirY < 0)
	{
		pars->stepY = -1;
		pars->sideDistY = (pars->posY - pars->mapY) * pars->deltaDistY;
	}
	else
	{
		pars->stepY = 1;
		pars->sideDistY = (pars->mapY + 1.0 - pars->posY)
		* pars->deltaDistY;
	}
}

void	find_wall_hit(t_parsing *pars)
{
	while (pars->hit == 0)
	{
		if (pars->sideDistX < pars->sideDistY)
		{
			pars->sideDistX += pars->deltaDistX;
			pars->mapX += pars->stepX;
			pars->side = 0;
		}
		else
		{
			pars->sideDistY += pars->deltaDistY;
			pars->mapY += pars->stepY;
			pars->side = 1;
		}
		if (pars->worldMap[pars->mapX][pars->mapY] == '1')
			pars->hit = 1;
	}
}

void	draw_walldist_value(t_parsing *pars)
{
	if (pars->side == 0)
		pars->perpWallDist = (pars->mapX - pars->posX + (1 - pars->stepX)
		/ 2) / pars->rayDirX;
	else
		pars->perpWallDist = (pars->mapY - pars->posY + (1 - pars->stepY)
		/ 2) / pars->rayDirY;
	pars->lineHeight = (int)(pars->h / pars->perpWallDist);
	pars->drawStart = -pars->lineHeight / 2 + pars->h / 2;
	if (pars->drawStart < 0)
		pars->drawStart = 0;
	pars->drawEnd = pars->lineHeight / 2 + pars->h / 2;
	if (pars->drawEnd >= pars->h)
		pars->drawEnd = pars->h - 1;
	if (pars->side == 0)
		pars->wallX = pars->posY + pars->perpWallDist * pars->rayDirY;
	else
		pars->wallX = pars->posX + pars->perpWallDist * pars->rayDirX;
	pars->wallX -= floor(pars->wallX);
}

void	texture_value(t_parsing *pars)
{
	pars->texX = (int)(pars->wallX * (double)(pars->tex_wight));
	if (pars->side == 0 && pars->rayDirX > 0)
		pars->texX = pars->tex_wight - pars->texX - 1;
	if (pars->side == 1 && pars->rayDirY < 0)
		pars->texX = pars->tex_wight - pars->texX - 1;
	pars->step = 1.0 * (double)pars->tex_height / (double)pars->lineHeight;
	pars->texPos = (double)(pars->drawStart - pars->h / 2 +
	pars->lineHeight / 2) * pars->step;
}

void	raycasting(t_parsing *pars)
{
	int x;

	x = 0;
	while (x < pars->w)
	{
		initializes_raycasting_value(pars, x);
		side_value(pars);
		find_wall_hit(pars);
		draw_walldist_value(pars);
		texture_value(pars);
		color_ceiling(pars, x);
		while (pars->drawStart <= pars->drawEnd)
			draw_wall(pars, x);
		color_floor(pars, x);
		pars->z_buffer[x] = pars->perpWallDist;
		x++;
	}
	raycasting_sprite(pars);
	if (pars->save == 1)
	{
		make_bmp(pars);
		pars->save = 0;
	}
	mlx_put_image_to_window(pars->mlx, pars->win, pars->img, 0, 0);
}
