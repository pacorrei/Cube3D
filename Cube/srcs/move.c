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
	if (pars->worldMap[(int)(pars->posX + pars->planeX *
	pars->moveSpeed)][(int)pars->posY] != '1')
		pars->posX += pars->planeX * pars->moveSpeed;
	if (pars->worldMap[(int)pars->posX][(int)(pars->posY +
	pars->planeY * pars->moveSpeed)] != '1')
		pars->posY += pars->planeY * pars->moveSpeed;
	raycasting(pars);
}

void	move_left(t_parsing *pars)
{
	if (pars->worldMap[(int)(pars->posX - pars->planeX *
	pars->moveSpeed)][(int)pars->posY] != '1')
		pars->posX -= pars->planeX * pars->moveSpeed;
	if (pars->worldMap[(int)pars->posX][(int)(pars->posY -
	pars->planeY * pars->moveSpeed)] != '1')
		pars->posY -= pars->planeY * pars->moveSpeed;
	raycasting(pars);
}

void	move_up(t_parsing *pars)
{
	if (pars->worldMap[(int)(pars->posX + pars->dirX *
	pars->moveSpeed)][(int)pars->posY] != '1')
		pars->posX += pars->dirX * pars->moveSpeed;
	if (pars->worldMap[(int)pars->posX][(int)(pars->posY +
	pars->dirY * pars->moveSpeed)] != '1')
		pars->posY += pars->dirY * pars->moveSpeed;
	raycasting(pars);
}

void	move_down(t_parsing *pars)
{
	if (pars->worldMap[(int)(pars->posX - pars->dirX *
	pars->moveSpeed)][(int)pars->posY] != '1')
		pars->posX -= pars->dirX * pars->moveSpeed;
	if (pars->worldMap[(int)pars->posX][(int)(pars->posY -
	pars->dirY * pars->moveSpeed)] != '1')
		pars->posY -= pars->dirY * pars->moveSpeed;
	raycasting(pars);
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
	if (pars->key_d == 0 && pars->key_left == 0 && pars->key_q == 0 &&
	pars->key_right == 0 && pars->key_s == 0 && pars->key_z == 0)
		raycasting(pars);
	return (0);
}
