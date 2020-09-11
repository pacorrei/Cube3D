/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2020/04/26 11:03:38 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

void	draw_sprite_value(t_parsing *pars)
{
	if (pars->spri_drawstarty < 0)
		pars->spri_drawstarty = 0;
	pars->spri_drawendy = pars->spriteheight / 2 + pars->h / 2;
	if (pars->spri_drawendy >= pars->h)
		pars->spri_drawendy = pars->h - 1;
	pars->spritewidth = abs((int)(pars->h / (pars->transformy)));
	pars->spri_drawstartx = -pars->spritewidth / 2 + pars->spritescreenx;
	if (pars->spri_drawstartx < 0)
		pars->spri_drawstartx = 0;
	pars->spri_drawendx = pars->spritewidth / 2 + pars->spritescreenx;
	if (pars->spri_drawendx >= pars->w)
		pars->spri_drawendx = pars->w - 1;
	pars->stripe = pars->spri_drawstartx;
}

void	initializes_sprite_value(t_parsing *pars, int i)
{
	pars->spritex = pars->pos_sprite[pars->sprite_order[i]][0]
	+ 0.5 - pars->posx;
	pars->spritey = pars->pos_sprite[pars->sprite_order[i]][1]
	+ 0.5 - pars->posy;
	pars->invdet = 1.0 / (pars->planex * pars->diry -
	pars->dirx * pars->planey);
	pars->transformx = pars->invdet * (pars->diry *
	pars->spritex - pars->dirx * pars->spritey);
	pars->transformy = pars->invdet * (-pars->planey *
	pars->spritex + pars->planex * pars->spritey);
	pars->spritescreenx = (int)((pars->w / 2) * (1 +
	pars->transformx / pars->transformy));
	pars->spriteheight = abs((int)(pars->h / (pars->transformy)));
	pars->spri_drawstarty = -pars->spriteheight / 2 + pars->h / 2;
}

int		draw_sprite(t_parsing *pars, int y)
{
	int d;

	d = (y + 1) * 256 - pars->h * 128 +
	pars->spriteheight * 128;
	pars->spri_texy = ((d * pars->tex_height) /
	pars->spriteheight) / 256;
	pars->alpha = pars->addr_s[pars->line_length_s *
	pars->spri_texy + pars->spri_texx * 4];
	pars->red = pars->addr_s[pars->line_length_s *
	pars->spri_texy + pars->spri_texx * 4 + 1];
	pars->green = pars->addr_s[pars->line_length_s *
	pars->spri_texy + pars->spri_texx * 4 + 2];
	pars->blue = pars->addr_s[pars->line_length_s *
	pars->spri_texy + pars->spri_texx * 4 + 3];
	if (!(pars->red == 0 && pars->blue == 0 && pars->green == 0))
		my_mlx_pixel_put(pars, pars->stripe, y, 255);
	y++;
	return (y);
}

void	verif_sprites_on_screen(t_parsing *pars)
{
	int y;

	pars->spri_texx = (int)(256 * (pars->stripe -
	(-pars->spritewidth / 2 + pars->spritescreenx)) *
	pars->tex_wight / pars->spritewidth) / 256;
	if (pars->transformy > 0 && pars->stripe > 0 &&
	pars->stripe < pars->w && pars->transformy <
	pars->z_buffer[pars->stripe])
	{
		y = pars->spri_drawstarty;
		while (y < pars->spri_drawendy)
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
		pars->sprite_dist[i] = ((pars->posx - pars->pos_sprite[i][0]) *
		(pars->posx - pars->pos_sprite[i][0])
		+ (pars->posy - pars->pos_sprite[i][1]) *
		(pars->posy - pars->pos_sprite[i][1]));
		i++;
	}
	sort_sprites(pars);
	i = 0;
	while (i < pars->nb_sprite)
	{
		initializes_sprite_value(pars, i);
		draw_sprite_value(pars);
		while (pars->stripe < pars->spri_drawendx)
			verif_sprites_on_screen(pars);
		i++;
	}
}
