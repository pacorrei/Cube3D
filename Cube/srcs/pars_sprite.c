/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2020/04/26 11:03:38 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

void	sort_sprites(t_parsing *pars)
{
	int i;
	int j;
	int copy;

	j = 0;
	while (j < pars->nb_sprite)
	{
		i = 0;
		while (i + 1 < pars->nb_sprite)
		{
			if (pars->sprite_dist[i] < pars->sprite_dist[i + 1])
			{
				copy = pars->sprite_dist[i];
				pars->sprite_dist[i] = pars->sprite_dist[i + 1];
				pars->sprite_dist[i + 1] = copy;
				copy = pars->sprite_order[i];
				pars->sprite_order[i] = pars->sprite_order[i + 1];
				pars->sprite_order[i + 1] = copy;
			}
			i++;
		}
		j++;
	}
}

int		fill_sprite_pos(t_parsing *pars, int i, int j, int k)
{
	pars->pos_sprite[k] = malloc(sizeof(int) * (2 + 1));
	pars->pos_sprite[k][0] = i;
	pars->pos_sprite[k][1] = j;
	pars->pos_sprite[k][2] = '\0';
	k++;
	return (k);
}

void	find_sprite_pos(t_parsing *pars)
{
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	pars->pos_sprite = (int**)malloc(sizeof(int*) * (pars->nb_sprite + 1));
	pars->pos_sprite[pars->nb_sprite] = NULL;
	pars->sprite_order = malloc(sizeof(int) * (pars->nb_sprite + 1));
	pars->sprite_order[pars->nb_sprite] = '\0';
	pars->sprite_dist = malloc(sizeof(int) * (pars->nb_sprite + 1));
	pars->sprite_dist[pars->nb_sprite] = '\0';
	while (pars->worldMap[i] != NULL)
	{
		j = 0;
		while (pars->worldMap[i][j] != '\0')
		{
			if (pars->worldMap[i][j] == '2')
				k = fill_sprite_pos(pars, i, j, k);
			j++;
		}
		i++;
	}
}
