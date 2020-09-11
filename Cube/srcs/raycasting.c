/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2020/04/26 11:03:38 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

void	side_value(t_parsing *pars)
{
	if (pars->raydirx < 0)
	{
		pars->stepx = -1;
		pars->sidedistx = (pars->posx - pars->mapx) * pars->deltadistx;
	}
	else
	{
		pars->stepx = 1;
		pars->sidedistx = (pars->mapx + 1.0 - pars->posx) *
		pars->deltadistx;
	}
	if (pars->raydiry < 0)
	{
		pars->stepy = -1;
		pars->sidedisty = (pars->posy - pars->mapy) * pars->deltadisty;
	}
	else
	{
		pars->stepy = 1;
		pars->sidedisty = (pars->mapy + 1.0 - pars->posy)
		* pars->deltadisty;
	}
}

void	find_wall_hit(t_parsing *pars)
{
	while (pars->hit == 0)
	{
		if (pars->sidedistx < pars->sidedisty)
		{
			pars->sidedistx += pars->deltadistx;
			pars->mapx += pars->stepx;
			pars->side = 0;
		}
		else
		{
			pars->sidedisty += pars->deltadisty;
			pars->mapy += pars->stepy;
			pars->side = 1;
		}
		if (pars->worldmap[pars->mapx][pars->mapy] == '1')
			pars->hit = 1;
	}
}

void	draw_walldist_value(t_parsing *pars)
{
	if (pars->side == 0)
		pars->perpwalldist = (pars->mapx - pars->posx + (1 - pars->stepx)
		/ 2) / pars->raydirx;
	else
		pars->perpwalldist = (pars->mapy - pars->posy + (1 - pars->stepy)
		/ 2) / pars->raydiry;
	pars->lineheight = (int)(pars->h / pars->perpwalldist);
	pars->drawstart = -pars->lineheight / 2 + pars->h / 2;
	if (pars->drawstart < 0)
		pars->drawstart = 0;
	pars->drawend = pars->lineheight / 2 + pars->h / 2;
	if (pars->drawend >= pars->h)
		pars->drawend = pars->h - 1;
	if (pars->side == 0)
		pars->wallx = pars->posy + pars->perpwalldist * pars->raydiry;
	else
		pars->wallx = pars->posx + pars->perpwalldist * pars->raydirx;
	pars->wallx -= floor(pars->wallx);
}

void	texture_value(t_parsing *pars)
{
	pars->texx = (int)(pars->wallx * (double)(pars->tex_wight));
	if (pars->side == 0 && pars->raydirx > 0)
		pars->texx = pars->tex_wight - pars->texx - 1;
	if (pars->side == 1 && pars->raydiry < 0)
		pars->texx = pars->tex_wight - pars->texx - 1;
	pars->step = 1.0 * (double)pars->tex_height / (double)pars->lineheight;
	pars->texpos = (double)(pars->drawstart - pars->h / 2 +
	pars->lineheight / 2) * pars->step;
}

void	raycasting(t_parsing *pars)
{
	int x;

	x = 0;
	pars->w = pars->res_x;
	while (x < pars->w)
	{
		initializes_raycasting_value(pars, x);
		side_value(pars);
		find_wall_hit(pars);
		draw_walldist_value(pars);
		texture_value(pars);
		color_ceiling(pars, x);
		while (pars->drawstart <= pars->drawend)
			draw_wall(pars, x);
		color_floor(pars, x);
		pars->z_buffer[x] = pars->perpwalldist;
		x++;
	}
	raycasting_sprite(pars);
	if (pars->save == 1)
		make_bmp(pars);
	mlx_put_image_to_window(pars->mlx, pars->win, pars->img, 0, 0);
}
