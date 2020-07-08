/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_identifiers4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:05:54 by pacorrei          #+#    #+#             */
/*   Updated: 2020/01/08 00:32:10 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

void    attribute_path_we(t_parsing *pars, int i, int j, int k)
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
     printf("we ;%s\n", pars->path_txt_we);
}

void    identifiers_we(t_parsing *pars, int i, int j)
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
}

void    attribute_path_ea(t_parsing *pars, int i, int j, int k)
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
     printf("ea ;%s\n", pars->path_txt_ea);
}

void    identifiers_ea(t_parsing *pars, int i, int j)
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
}