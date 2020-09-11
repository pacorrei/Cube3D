/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2020/04/26 11:03:38 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

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
	return (0);
}
