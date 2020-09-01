/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_identifiers3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:05:54 by pacorrei          #+#    #+#             */
/*   Updated: 2020/08/20 17:39:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

void	verif_path_no(t_parsing *pars, char *path)
{
    pars->ptr_no = mlx_xpm_file_to_image(pars->mlx, path, &pars->tex_height, &pars->tex_wight);
    if (pars->ptr_no == NULL)
         error_informations(pars);
	pars->addr_no = mlx_get_data_addr(pars->ptr_no, &pars->bits_per_pixel_no,  &pars->line_length_no,  &pars->endian_no);
}
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
    if (pars->path_txt_no != NULL)
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
    attribute_path_no(pars, i, j, k);
    verif_path_no(pars, pars->path_txt_no);
}

void	verif_path_so(t_parsing *pars, char *path)
{
    pars->ptr_so = mlx_xpm_file_to_image(pars->mlx, path, &pars->tex_height, &pars->tex_wight);
    if (pars->ptr_so == NULL)
         error_informations(pars);
	pars->addr_so = mlx_get_data_addr(pars->ptr_so, &pars->bits_per_pixel_so,  &pars->line_length_so,  &pars->endian_so);
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
    if (pars->path_txt_so != NULL)
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
    attribute_path_so(pars, i, j, k);
    verif_path_so(pars, pars->path_txt_so);
}