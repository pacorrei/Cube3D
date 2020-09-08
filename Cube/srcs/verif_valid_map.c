/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_valid_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2020/04/26 11:03:38 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

void	make_world_map(t_parsing *pars, int imin, int imax)
{
	int i;
	int j;

	i = imax - imin;
	pars->worldMap = (char**)malloc(sizeof(char*) * (i + 1));
	pars->worldMap[i] = NULL;
	i--;
	while (imin < imax)
	{
		pars->worldMap[i] = ft_strdup(pars->info[imin]);
		imin++;
		j = 0;
		while (pars->worldMap[i][j] != '\0')
		{
			if (pars->worldMap[i][j] == 'N' || pars->worldMap[i][j] == 'S'
			|| pars->worldMap[i][j] == 'E' || pars->worldMap[i][j] == 'W')
			{
				pars->posY = j + 0.5;
				pars->posX = i + 0.5;
			}
			j++;
		}
		i--;
	}
	find_sprite_pos(pars);
}

int		verif_arg_map(t_parsing *pars, int i, int j)
{
	if (pars->verif == 0 && (pars->info[i][j] == 'N'
	|| pars->info[i][j] == 'S'
	|| pars->info[i][j] == 'W' || pars->info[i][j] == 'E'))
	{
		pars->pos_player = pars->info[i][j];
		pars->verif++;
		j++;
	}
	if (pars->info[i][j] == '2')
		pars->nb_sprite++;
	if (pars->line_empty == 0 && pars->info[i][j] == '1')
		pars->line_empty = 1;
	if ((pars->info[i][j] != ' ' && pars->info[i][j] != '1' &&
	pars->info[i][j] != '2' && pars->info[i][j] != '0') || pars->verif > 1)
		error_informations(pars);
	j++;
	return (j);
}

void	verif_valid_map(t_parsing *pars, int i, int j)
{
	int verif2;
	int copy_i;

	pars->verif = 0;
	verif2 = 0;
	copy_i = i;
	pars->line_empty = 0;
	pars->pos_player = 0;
	while (pars->info[i] != NULL)
	{
		while (pars->info[i][j] != '\0')
		{
			j = verif_arg_map(pars, i, j);
		}
		if (verif2 == 0 && pars->line_empty == 0)
		{
			verif2 = 1;
			make_world_map(pars, copy_i, i);
		}
		pars->line_empty = 0;
		i++;
		j = 0;
	}
	if (pars->pos_player == 0)
		error_miss_informations(pars);
}
