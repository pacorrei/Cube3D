/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2020/04/26 11:03:38 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

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

void	color_ceiling(t_parsing *pars, int x)
{
	int i;

	i = 0;
	while (i < pars->drawstart)
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

	i = pars->drawend + 1;
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
