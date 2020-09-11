/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_informations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2020/04/26 11:03:38 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

void	find_identifiers(t_parsing *pars, int i, int j)
{
	if (pars->info[i][j] == 'R')
		identifiers_r(pars, i, j + 1);
	if (pars->info[i][j] == 'C')
		identifiers_c(pars, i, j + 1);
	if (pars->info[i][j] == 'S' && pars->info[i][j + 1] != 'O')
		identifiers_s(pars, i, j + 1);
	if (pars->info[i][j] == 'F')
		identifiers_f(pars, i, j + 1);
	if (pars->info[i][j] == 'N' && pars->info[i][j + 1] == 'O')
		identifiers_no(pars, i, j + 2);
	if (pars->info[i][j] == 'S' && pars->info[i][j + 1] == 'O')
		identifiers_so(pars, i, j + 2);
	if (pars->info[i][j] == 'W' && pars->info[i][j + 1] == 'E')
		identifiers_we(pars, i, j + 2);
	if (pars->info[i][j] == 'E' && pars->info[i][j + 1] == 'A')
		identifiers_ea(pars, i, j + 2);
	return ;
}

void	verif_identifiers_info(t_parsing *pars, int i, int j)
{
	if ((pars->info[i][j] == 'R' ||
	pars->info[i][j] == 'C' || pars->info[i][j] == 'S' ||
	pars->info[i][j] == 'F' || (pars->info[i][j] == 'N' &&
	pars->info[i][j + 1] == 'O') || (pars->info[i][j] == 'S' &&
	pars->info[i][j + 1] == 'O') || (pars->info[i][j] == 'W' &&
	pars->info[i][j + 1] == 'E') || (pars->info[i][j] == 'E' &&
	pars->info[i][j + 1] == 'A')))
	{
		find_identifiers(pars, i, j);
		pars->verif = 1;
	}
}

void	verif_map_informations(t_parsing *pars, int i, int j)
{
	if ((pars->info[i][j] == '1' ||
	pars->info[i][j] == '0' || pars->info[i][j] == '2'))
	{
		verif_valid_map(pars, i, j);
		verif_close_map(pars, i, j);
		pars->map_verif = 1;
	}
}

void	verif_informations(t_parsing *pars, int i, int j)
{
	if (pars->info[i][j] != ' ' && pars->info[i][j] != 'R' &&
	pars->info[i][j] != 'C' && pars->info[i][j] != 'S' &&
	pars->info[i][j] != 'F' && (pars->info[i][j] != 'N' &&
	pars->info[i][j + 1] != 'O') && (pars->info[i][j] != 'S' &&
	pars->info[i][j + 1] != 'O') && (pars->info[i][j] != 'W' &&
	pars->info[i][j + 1] != 'E') && (pars->info[i][j] != 'E' &&
	pars->info[i][j + 1] != 'A'))
		error_informations(pars);
	if ((pars->info[i][j] == 'N' &&
	pars->info[i][j + 1] != 'O') || (pars->info[i][j] == 'S' &&
	pars->info[i][j + 1] != 'O' && pars->info[i][j + 1] != ' ') ||
	(pars->info[i][j] == 'W' && pars->info[i][j + 1] != 'E') ||
	(pars->info[i][j] == 'E' && pars->info[i][j + 1] != 'A'))
		error_informations(pars);
}

void	find_informations(t_parsing *pars)
{
	int i;
	int j;

	i = 0;
	while (pars->info[i] != NULL)
	{
		j = 0;
		pars->verif = 0;
		while (pars->info[i][j] != '\0')
		{
			if (pars->verif == 0 && pars->map_verif == 0)
				verif_map_informations(pars, i, j);
			if (pars->verif == 0 && pars->map_verif == 0)
				verif_informations(pars, i, j);
			if (pars->verif == 0 && pars->map_verif == 0)
				verif_identifiers_info(pars, i, j);
			j++;
		}
		i++;
	}
	if (pars->map_verif == 0 || pars->verif_r == 0 || pars->verif_f == 0
	|| pars->verif_c == 0 || pars->verif_s == 0 || pars->verif_no == 0
	|| pars->verif_so == 0 || pars->verif_ea == 0 || pars->verif_we == 0)
		error_miss_informations(pars);
	ft_putstr("Valide Map");
}
