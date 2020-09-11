/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2020/04/26 11:03:38 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

void	move_right(t_parsing *pars)
{
	if (pars->worldmap[(int)(pars->posx + pars->planex *
	pars->movespeed)][(int)pars->posy] != '1')
		pars->posx += pars->planex * pars->movespeed;
	if (pars->worldmap[(int)pars->posx][(int)(pars->posy +
	pars->planey * pars->movespeed)] != '1')
		pars->posy += pars->planey * pars->movespeed;
}

void	move_left(t_parsing *pars)
{
	if (pars->worldmap[(int)(pars->posx - pars->planex *
	pars->movespeed)][(int)pars->posy] != '1')
		pars->posx -= pars->planex * pars->movespeed;
	if (pars->worldmap[(int)pars->posx][(int)(pars->posy -
	pars->planey * pars->movespeed)] != '1')
		pars->posy -= pars->planey * pars->movespeed;
}

void	move_up(t_parsing *pars)
{
	if (pars->worldmap[(int)(pars->posx + pars->dirx *
	pars->movespeed)][(int)pars->posy] != '1')
		pars->posx += pars->dirx * pars->movespeed;
	if (pars->worldmap[(int)pars->posx][(int)(pars->posy +
	pars->diry * pars->movespeed)] != '1')
		pars->posy += pars->diry * pars->movespeed;
}

void	move_down(t_parsing *pars)
{
	if (pars->worldmap[(int)(pars->posx - pars->dirx *
	pars->movespeed)][(int)pars->posy] != '1')
		pars->posx -= pars->dirx * pars->movespeed;
	if (pars->worldmap[(int)pars->posx][(int)(pars->posy -
	pars->diry * pars->movespeed)] != '1')
		pars->posy -= pars->diry * pars->movespeed;
}

int		key_action(t_parsing *pars)
{
	if (pars->key_echap == 1)
	{
		mlx_destroy_window(pars->mlx, pars->win);
		free_all(pars);
		exit(0);
	}
	if (pars->key_d == 1)
		move_right(pars);
	if (pars->key_q == 1)
		move_left(pars);
	if (pars->key_z == 1)
		move_up(pars);
	if (pars->key_s == 1)
		move_down(pars);
	if (pars->key_right == 1)
		turn_right(pars);
	if (pars->key_left == 1)
		turn_left(pars);
	raycasting(pars);
	return (0);
}
