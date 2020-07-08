/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_valid_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2020/04/26 11:03:38 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

void    verif_valid_map(t_parsing *pars, int i, int j)
{
    int verif;

    verif = 0;
    pars->pos_player = 0;
    while (pars->info[i] != NULL)
    {
        while (pars->info[i][j] != '\0')
        {
            if (verif == 0 && (pars->info[i][j] == 'N' || pars->info[i][j] == 'S'
            || pars->info[i][j] == 'W' || pars->info[i][j] == 'E'))
            {
                pars->pos_player = pars->info[i][j];
                verif++;
                j++;
            }
            if ((pars->info[i][j] != ' ' && pars->info[i][j] != '1' &&
            pars->info[i][j] != '2' && pars->info[i][j] != '0') || verif > 1)
                error_informations(pars);
            j++;
        }
        i++;
        j = 0;
    }
    if (pars->pos_player == 0)
        error_miss_informations(pars);
}

void       verif_first_last_line(t_parsing *pars, int i, int j)
{
    j = 0;
    while (pars->info[i][j] != '\0')
    {
        if (pars->info[i][j] != ' ' && pars->info[i][j] != '1')
            error_informations(pars);
        j++;
    }
}

void    verif_inside_map(t_parsing *pars, int i, int j)
{
    if (pars->info[i][j] == '0' && pars->info[i][j + 1] != '0' &&
    pars->info[i][j + 1] != pars->pos_player && pars->info[i][j + 1] != '1'
    && pars->info[i][j + 1] != '2')
        error_informations(pars);
    if (pars->info[i][j] == '0' && pars->info[i][j - 1] != '0' &&
    pars->info[i][j - 1] != '1' && pars->info[i][j - 1] != pars->pos_player
    && pars->info[i][j - 1] != '2')
        error_informations(pars);
    if (pars->info[i][j] == '0' && pars->info[i + 1][j] != '0' &&
    pars->info[i + 1][j] != '1' && pars->info[i + 1][j] != pars->pos_player
    && pars->info[i + 1][j] != '2')
        error_informations(pars);
    if (pars->info[i][j] == '0' && pars->info[i - 1][j] != '0' &&
    pars->info[i - 1][j] != '1' && pars->info[i - 1][j] != pars->pos_player
    && pars->info[i - 1][j] != '0')
        error_informations(pars);  
}

void    verif_close_map(t_parsing *pars, int i, int j)
{
    int     verif;
    char    last_char;

    verif = 0;
    verif_first_last_line(pars, i, j);
    i++;
    while (pars->info[i + 1] != NULL)
    {
        j = 0;
        while (pars->info[i][j] != '\0')
        {
            if (pars->info[i][j] == '1' && verif == 0)
                verif = 1;
            if (verif == 0 && (pars->info[i][j] == '0' || pars->info[i][j] == '2' ||
            pars->info[i][j] == pars->pos_player))
                error_informations(pars);
            if (pars->info[i][j] != ' ')
                last_char = pars->info[i][j];
            verif_inside_map(pars, i, j);
            j++;
        }
        i++;
        verif = 0;
        if (last_char == '0' || last_char == '2' ||
        last_char == pars->pos_player)
            error_informations(pars);
    }
    verif_first_last_line(pars, i, j);
}