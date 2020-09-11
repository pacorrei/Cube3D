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
	pars->olddirx = pars->dirx;
	pars->dirx = pars->dirx * cos(pars->rotspeed) -
	pars->diry * sin(pars->rotspeed);
	pars->diry = pars->olddirx * sin(pars->rotspeed) +
	pars->diry * cos(pars->rotspeed);
	pars->oldplanex = pars->planex;
	pars->planex = pars->planex * cos(pars->rotspeed) -
	pars->planey * sin(pars->rotspeed);
	pars->planey = pars->oldplanex * sin(pars->rotspeed) +
	pars->planey * cos(pars->rotspeed);
}

void	turn_left(t_parsing *pars)
{
	pars->olddirx = pars->dirx;
	pars->dirx = pars->dirx * cos(-pars->rotspeed) -
	pars->diry * sin(-pars->rotspeed);
	pars->diry = pars->olddirx * sin(-pars->rotspeed) +
	pars->diry * cos(-pars->rotspeed);
	pars->oldplanex = pars->planex;
	pars->planex = pars->planex * cos(-pars->rotspeed) -
	pars->planey * sin(-pars->rotspeed);
	pars->planey = pars->oldplanex * sin(-pars->rotspeed) +
	pars->planey * cos(-pars->rotspeed);
}
