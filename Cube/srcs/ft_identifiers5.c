/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_identifiers5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:05:54 by pacorrei          #+#    #+#             */
/*   Updated: 2020/08/20 17:40:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

void	attribute_path_s(t_parsing *pars, int i, int j, int k)
{
	int l;

	if (!(pars->path_txt_s = malloc(sizeof(char) * (k + 1))))
		error_malloc(pars);
	pars->path_txt_s[k] = '\0';
	l = k - 1;
	j = 0;
	k = 0;
	while (pars->info[i][j] != '.')
		j++;
	while (l >= 0)
	{
		pars->path_txt_s[k] = pars->info[i][j];
		k++;
		j++;
		l--;
	}
}

void	identifiers_s(t_parsing *pars, int i, int j)
{
	int k;

	k = 0;
	if (pars->verif_s == 1 || pars->path_txt_s != NULL)
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
	attribute_path_s(pars, i, j, k);
	verif_path_s(pars, pars->path_txt_s);
	pars->verif_s = 1;
}
