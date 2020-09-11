/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2020/04/26 11:03:38 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

void	draw_wall(t_parsing *pars, int x)
{
	pars->texy = (int)pars->texpos;
	pars->texpos += pars->step;
	pars->addr_tex = get_addr_tex(pars);
	pars->line_length_tex = get_line_length_tex(pars);
	pars->alpha = pars->addr_tex[pars->line_length_tex * pars->texy +
	pars->texx * 4];
	pars->red = pars->addr_tex[pars->line_length_tex * pars->texy +
	pars->texx * 4 + 1];
	pars->green = pars->addr_tex[pars->line_length_tex * pars->texy +
	pars->texx * 4 + 2];
	pars->blue = pars->addr_tex[pars->line_length_tex * pars->texy +
	pars->texx * 4 + 3];
	my_mlx_pixel_put(pars, x, pars->drawstart, 255);
	pars->drawstart++;
}

void	initializes_raycasting_value(t_parsing *pars, int x)
{
	pars->movespeed = 0.2;
	pars->rotspeed = 0.1;
	pars->h = pars->res_y;
	pars->camerax = (2 * x) / (double)pars->w - 1;
	pars->raydirx = pars->dirx + pars->planex * pars->camerax;
	pars->raydiry = pars->diry + pars->planey * pars->camerax;
	pars->mapx = (int)pars->posx;
	pars->mapy = (int)pars->posy;
	pars->deltadistx = fabs(1 / pars->raydirx);
	pars->deltadisty = fabs(1 / pars->raydiry);
	pars->hit = 0;
}
