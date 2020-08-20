/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_identifiers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:05:54 by pacorrei          #+#    #+#             */
/*   Updated: 2020/01/08 00:32:10 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

int		find_nb(t_parsing *pars, int i, int j)
{
    int     l;
	int		k;
	char	*copy;

	l = 0;
	k = 0;
	while (pars->info[i][j] >= '0' && pars->info[i][j] <= '9')
	{
		l++;
		j++;
	}
	if (!(copy = malloc(sizeof(char) * (l + 1))))
		return (-1);
	copy[l] = '\0';
	j = j - l;
	while (l-- > 0)
		copy[k++] = pars->info[i][j++];
	k = ft_atoi(copy);
    free(copy);
	return (k);
}

void    identifiers_r(t_parsing *pars, int i, int j)
{
    int verif;

    verif = 0;
    while (pars->info[i][j] != '\0')
    {
        if (pars->info[i][j] != ' ' && (pars->info[i][j] < '0' || pars->info[i][j] > '9'))
            error_informations(pars);
        if (verif == 2 && pars->info[i][j] != ' ' )
            error_informations(pars);
        if (pars->info[i][j] >= '0' && pars->info[i][j] <= '9')
        {
            if (verif == 0 && pars->info[i][j] >= '0' && pars->info[i][j] <= '9')
            {
                pars->res_x = find_nb(pars, i, j);
                if (pars->res_x <= 0)
                    error_informations(pars);
                verif = 1;
                while (pars->info[i][j] >= '0' && pars->info[i][j] <= '9' && pars->info[i][j + 1] != '\0')
                    j++;
            }
            if (verif == 1 && pars->info[i][j] >= '0' && pars->info[i][j] <= '9')
            {
                pars->res_y = find_nb(pars, i, j);
                 if (pars->res_y <= 0)
                    error_informations(pars);
                verif = 2;
                while (pars->info[i][j] >= '0' && pars->info[i][j] <= '9' && pars->info[i][j + 1] != '\0')
                    j++;
            }
        }
        j++;
    }
    if (verif == 0 || verif == 1)
        error_miss_informations(pars);
}