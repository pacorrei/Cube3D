/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2020/04/26 11:03:38 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

void	turn_right(t_parsing *pars)
{
	pars->oldDirX = pars->dirX;
	pars->dirX = pars->dirX * cos(pars->rotSpeed) -
	pars->dirY * sin(pars->rotSpeed);
	pars->dirY = pars->oldDirX * sin(pars->rotSpeed) +
	pars->dirY * cos(pars->rotSpeed);
	pars->oldPlaneX = pars->planeX;
	pars->planeX = pars->planeX * cos(pars->rotSpeed) -
	pars->planeY * sin(pars->rotSpeed);
	pars->planeY = pars->oldPlaneX * sin(pars->rotSpeed) +
	pars->planeY * cos(pars->rotSpeed);
	raycasting(pars);
}

void	turn_left(t_parsing *pars)
{
	pars->oldDirX = pars->dirX;
	pars->dirX = pars->dirX * cos(-pars->rotSpeed) -
	pars->dirY * sin(-pars->rotSpeed);
	pars->dirY = pars->oldDirX * sin(-pars->rotSpeed) +
	pars->dirY * cos(-pars->rotSpeed);
	pars->oldPlaneX = pars->planeX;
	pars->planeX = pars->planeX * cos(-pars->rotSpeed) -
	pars->planeY * sin(-pars->rotSpeed);
	pars->planeY = pars->oldPlaneX * sin(-pars->rotSpeed) +
	pars->planeY * cos(-pars->rotSpeed);
	raycasting(pars);
}
