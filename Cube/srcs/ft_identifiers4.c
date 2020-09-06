/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_identifiers4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:05:54 by pacorrei          #+#    #+#             */
/*   Updated: 2020/08/20 17:40:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

void	attribute_path_we(t_parsing *pars, int i, int j, int k)
{
	int l;

	if (!(pars->path_txt_we = malloc(sizeof(char) * (k + 1))))
		error_malloc(pars);
	pars->path_txt_we[k] = '\0';
	l = k - 1;
	j = 0;
	k = 0;
	while (pars->info[i][j] != '.')
		j++;
	while (l >= 0)
	{
		pars->path_txt_we[k] = pars->info[i][j];
		k++;
		j++;
		l--;
	}
}

void	identifiers_we(t_parsing *pars, int i, int j)
{
	int k;

	k = 0;
	if (pars->path_txt_we != NULL)
		error_informations(pars);
	while (pars->info[i][j] != '.' && pars->info[i][j] != '\0')
	{
		if (pars->info[i][j] != ' ')
			error_informations(pars);
		j++;
	}
	while (pars->info[i][j] != ' ' && pars->info[i][j] != '\0')
	{
		j++;
		k++;
	}
	while (pars->info[i][j] != '\0')
	{
		if (pars->info[i][j] != ' ')
			error_informations(pars);
		j++;
	}
	attribute_path_we(pars, i, j, k);
	verif_path_we(pars, pars->path_txt_we);
}

void	attribute_path_ea(t_parsing *pars, int i, int j, int k)
{
	int l;

	if (!(pars->path_txt_ea = malloc(sizeof(char) * (k + 1))))
		error_malloc(pars);
	pars->path_txt_ea[k] = '\0';
	l = k - 1;
	j = 0;
	k = 0;
	while (pars->info[i][j] != '.')
		j++;
	while (l >= 0)
	{
		pars->path_txt_ea[k] = pars->info[i][j];
		k++;
		j++;
		l--;
	}
}

void	identifiers_ea(t_parsing *pars, int i, int j)
{
	int k;

	k = 0;
	if (pars->path_txt_ea != NULL)
		error_informations(pars);
	while (pars->info[i][j] != '.' && pars->info[i][j] != '\0')
	{
		if (pars->info[i][j] != ' ')
			error_informations(pars);
		j++;
	}
	while (pars->info[i][j] != ' ' && pars->info[i][j] != '\0')
	{
		j++;
		k++;
	}
	while (pars->info[i][j] != '\0')
	{
		if (pars->info[i][j] != ' ')
			error_informations(pars);
		j++;
	}
	attribute_path_ea(pars, i, j, k);
	verif_path_ea(pars, pars->path_txt_ea);
}
