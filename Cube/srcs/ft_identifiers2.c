/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_identifiers2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:05:54 by pacorrei          #+#    #+#             */
/*   Updated: 2020/01/08 00:32:10 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

int		search_nb_c(t_parsing *pars, int i, int j)
{
	if (pars->verif == 0 && pars->info[i][j] >= '0' && pars->info[i][j] <= '9')
	{
		pars->r_ceil = find_nb(pars, i, j);
		pars->verif = 1;
		while (pars->info[i][j] >= '0' && pars->info[i][j] <= '9'
		&& pars->info[i][j + 1] != '\0')
			j++;
	}
	if (pars->verif == 1 && pars->info[i][j] >= '0' && pars->info[i][j] <= '9')
	{
		pars->g_ceil = find_nb(pars, i, j);
		pars->verif = 2;
		while (pars->info[i][j] >= '0' && pars->info[i][j] <= '9'
		&& pars->info[i][j + 1] != '\0')
			j++;
	}
	if (pars->verif == 2 && pars->info[i][j] >= '0' && pars->info[i][j] <= '9')
	{
		pars->b_ceil = find_nb(pars, i, j);
		pars->verif = 3;
		while (pars->info[i][j] >= '0' && pars->info[i][j] <= '9'
		&& pars->info[i][j + 1] != '\0')
			j++;
	}
	return (j);
}

void	identifiers_c(t_parsing *pars, int i, int j)
{
	if (pars->verif_c == 1)
		error_informations(pars);
	pars->verif = 0;
	while (pars->info[i][j] != '\0')
	{
		if (pars->info[i][j] != ' ' && (pars->info[i][j] < '0'
		|| pars->info[i][j] > '9') &&
		pars->info[i][j] != ',')
			error_informations(pars);
		if (pars->info[i][j] == ',' && ((pars->info[i][j + 1] < '0'
		|| pars->info[i][j + 1] > '9')
		|| (pars->info[i][j - 1] < '0' || pars->info[i][j - 1] > '9')))
			error_informations(pars);
		if (pars->verif == 3 && pars->info[i][j] != ' ')
			error_informations(pars);
		if (pars->info[i][j] >= '0' && pars->info[i][j] <= '9')
		{
			j = search_nb_c(pars, i, j);
		}
		j++;
	}
	if (pars->verif == 0 || pars->verif == 1 || pars->verif == 2)
		error_miss_informations(pars);
	pars->verif_c = 1;
}

int		search_nb_f(t_parsing *pars, int i, int j)
{
	if (pars->verif == 0 && pars->info[i][j] >= '0' && pars->info[i][j] <= '9')
	{
		pars->r_floor = find_nb(pars, i, j);
		pars->verif = 1;
		while (pars->info[i][j] >= '0' && pars->info[i][j] <= '9'
		&& pars->info[i][j + 1] != '\0')
			j++;
	}
	if (pars->verif == 1 && pars->info[i][j] >= '0' && pars->info[i][j] <= '9')
	{
		pars->g_floor = find_nb(pars, i, j);
		pars->verif = 2;
		while (pars->info[i][j] >= '0' && pars->info[i][j] <= '9'
		&& pars->info[i][j + 1] != '\0')
			j++;
	}
	if (pars->verif == 2 && pars->info[i][j] >= '0' && pars->info[i][j] <= '9')
	{
		pars->b_floor = find_nb(pars, i, j);
		pars->verif = 3;
		while (pars->info[i][j] >= '0' && pars->info[i][j] <= '9'
		&& pars->info[i][j + 1] != '\0')
			j++;
	}
	return (j);
}

void	identifiers_f(t_parsing *pars, int i, int j)
{
	if (pars->verif_f == 1)
		error_informations(pars);
	pars->verif = 0;
	while (pars->info[i][j] != '\0')
	{
		if (pars->info[i][j] != ' ' && (pars->info[i][j] < '0'
		|| pars->info[i][j] > '9') &&
		pars->info[i][j] != ',')
			error_informations(pars);
		if (pars->info[i][j] == ',' && ((pars->info[i][j + 1] < '0'
		|| pars->info[i][j + 1] > '9')
		|| (pars->info[i][j - 1] < '0' || pars->info[i][j - 1] > '9')))
			error_informations(pars);
		if (pars->verif == 3 && pars->info[i][j] != ' ')
			error_informations(pars);
		if (pars->info[i][j] >= '0' && pars->info[i][j] <= '9')
		{
			j = search_nb_f(pars, i, j);
		}
		j++;
	}
	if (pars->verif == 0 || pars->verif == 1 || pars->verif == 2)
		error_miss_informations(pars);
	pars->verif_f = 1;
}
