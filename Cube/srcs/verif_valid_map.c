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

void    sort_sprites(t_parsing *pars)
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


void    find_sprite_pos(t_parsing *pars)
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
             {
                 pars->pos_sprite[k] = malloc(sizeof(int) * (2 + 1));
                 pars->pos_sprite[k][0] = i;
                 pars->pos_sprite[k][1] = j;
                 pars->pos_sprite[k][2] = '\0';
                 k++;
             }
            j++;
         }
         i++;
    }
}

void    make_world_map(t_parsing *pars, int imin, int imax)
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
        while(pars->worldMap[i][j] != '\0')
        {
            if (pars->worldMap[i][j] == 'N' || pars->worldMap[i][j] == 'S'
            || pars->worldMap[i][j] == 'E' || pars->worldMap[i][j] == 'W')
            {
                pars->posY = j;
                pars->posX = i;
            }
            j++;
        }
        i--;
    }
    find_sprite_pos(pars);
}

void    verif_valid_map(t_parsing *pars, int i, int j)
{
    int verif;
    int verif2;
    int copy_i;
    int line_empty;

    verif = 0;
    verif2 = 0;
    copy_i = i;
    line_empty = 0;
    pars->pos_player = 0;
    while (pars->info[i] != NULL)
    {
        while (pars->info[i][j] != '\0')
        {
            if (verif == 0 && (pars->info[i][j] == 'N' || pars->info[i][j] == 'S'
            || pars->info[i][j] == 'W' || pars->info[i][j] == 'E'))
            {
                pars->pos_player = pars->info[i][j];
               // pars->posY = j;
                //pars->posX = i - copy_i;
                verif++;
                j++;
            }
            if (pars->info[i][j] == '2')
                pars->nb_sprite++;
            if (line_empty == 0 && pars->info[i][j] == '1')
                line_empty = 1;
            if ((pars->info[i][j] != ' ' && pars->info[i][j] != '1' &&
            pars->info[i][j] != '2' && pars->info[i][j] != '0') || verif > 1)
                error_informations(pars);
            j++;
        }
        if (verif2 == 0 && line_empty == 0)
        {
            verif2 = 1;
            make_world_map(pars, copy_i, i);
        }
        line_empty = 0;
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
    if ((pars->info[i][j] == '0' || pars->info[i][j] == '2') && pars->info[i][j + 1] != '0' &&
    pars->info[i][j + 1] != pars->pos_player && pars->info[i][j + 1] != '1'
    && pars->info[i][j + 1] != '2')
        error_informations(pars);
    if ((pars->info[i][j] == '0' || pars->info[i][j] == '2') && pars->info[i][j - 1] != '0' &&
    pars->info[i][j - 1] != '1' && pars->info[i][j - 1] != pars->pos_player
    && pars->info[i][j - 1] != '2')
        error_informations(pars);
    if ((pars->info[i][j] == '0' || pars->info[i][j] == '2') && pars->info[i + 1][j] != '0' &&
    pars->info[i + 1][j] != '1' && pars->info[i + 1][j] != pars->pos_player
    && pars->info[i + 1][j] != '2')
        error_informations(pars);
    if ((pars->info[i][j] == '0' || pars->info[i][j] == '2') && pars->info[i - 1][j] != '0' &&
    pars->info[i - 1][j] != '1' && pars->info[i - 1][j] != pars->pos_player
    && pars->info[i - 1][j] != '2')
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