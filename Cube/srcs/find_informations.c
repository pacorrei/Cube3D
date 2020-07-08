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

void    find_identifiers(t_parsing *pars, int i, int j)
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

void    find_informations(t_parsing *pars)
{
    int i;
    int j;
    int verif;
    int map_verif;

    i = 0;
    j = 0;
    verif = 0;
    map_verif = 0;
    while (pars->info[i] != NULL)
    {
        while (pars->info[i][j] != '\0')
        {
            //ft_putchar('a');
            //printf("%c\n", pars->info[i][j]);
            //printf("%d\n", i);
            //printf("%d\n", j);
            if (verif == 0 && map_verif == 0 && (pars->info[i][j] == '1' ||
            pars->info[i][j] == '0' || pars->info[i][j] == '2'))
            {
                ft_putstr("Verif map ");
                verif_valid_map(pars, i, j);
                ft_putstr(" Map close ");
                 verif_close_map(pars, i, j);
                ft_putstr(" Map ok");
                map_verif = 1;
            }
            if (verif == 0 && map_verif == 0 && (pars->info[i][j] != ' ' && pars->info[i][j] != 'R' &&
            pars->info[i][j] != 'C' && pars->info[i][j] != 'S' &&
            pars->info[i][j] != 'F' && (pars->info[i][j] != 'N' &&
            pars->info[i][j + 1] != 'O') && (pars->info[i][j] != 'S' &&
            pars->info[i][j + 1] != 'O') && (pars->info[i][j] != 'W' &&
            pars->info[i][j + 1] != 'E') && (pars->info[i][j] != 'E' &&
            pars->info[i][j + 1] != 'A')))
                error_informations(pars);
            if (verif == 0 && map_verif == 0 && ((pars->info[i][j] == 'N' &&
            pars->info[i][j + 1] != 'O') || (pars->info[i][j] == 'S' &&
            pars->info[i][j + 1] != 'O' && pars->info[i][j + 1] != ' ') ||
            (pars->info[i][j] == 'W' && pars->info[i][j + 1] != 'E') ||
            (pars->info[i][j] == 'E' && pars->info[i][j + 1] != 'A')))
                 error_informations(pars);
            if (verif == 0 && map_verif == 0 && (pars->info[i][j] == 'R' ||
            pars->info[i][j] == 'C' || pars->info[i][j] == 'S' ||
            pars->info[i][j] == 'F' || (pars->info[i][j] == 'N' &&
            pars->info[i][j + 1] == 'O') || (pars->info[i][j] == 'S' &&
            pars->info[i][j + 1] == 'O') || (pars->info[i][j] == 'W' &&
            pars->info[i][j + 1] == 'E') || (pars->info[i][j] == 'E' &&
            pars->info[i][j + 1] == 'A')))
            {
                verif = 1;
                printf("%c\n", pars->info[i][j]);
                find_identifiers(pars, i, j);
            }
            j++;
        }
        //ft_putchar('b');
        i++;
        j = 0;
        verif = 0;
    }
    if (map_verif == 0)
        error_miss_informations(pars);
}