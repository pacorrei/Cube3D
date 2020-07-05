/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_identifiers3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:05:54 by pacorrei          #+#    #+#             */
/*   Updated: 2020/01/08 00:32:10 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

void    attribute_path_no(t_parsing *pars, int i, int j, int k)
{
    int l;

    if (!(pars->path_txt_no = malloc(sizeof(char) * (k + 1))))
        error_malloc(pars);
    pars->path_txt_no[k] = '\0';
    l = k - 1;
    j = 0;
    k = 0;
    while (pars->info[i][j] != '.')
        j++;
    while (l >= 0)
    {
        pars->path_txt_no[k] = pars->info[i][j];
        k++;
        j++;
        l--;
    }
    printf("no ;%s\n", pars->path_txt_no);
}

void    identifiers_no(t_parsing *pars, int i, int j)
{
    int k;

    k = 0;
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
    }
    attribute_path_no(pars, i, j, k);
}

void    attribute_path_so(t_parsing *pars, int i, int j, int k)
{
    int l;

    if (!(pars->path_txt_so = malloc(sizeof(char) * (k + 1))))
        error_malloc(pars);
    pars->path_txt_so[k] = '\0';
    l = k - 1;
    j = 0;
    k = 0;
    while (pars->info[i][j] != '.')
        j++;
    while (l >= 0)
    {
        pars->path_txt_so[k] = pars->info[i][j];
        k++;
        j++;
        l--;
    }
     printf("so ;%s\n", pars->path_txt_so);
}

void    identifiers_so(t_parsing *pars, int i, int j)
{
    int k;

    k = 0;
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
    }
    attribute_path_so(pars, i, j, k);
}