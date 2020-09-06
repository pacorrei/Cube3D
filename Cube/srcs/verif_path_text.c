/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_path_text.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2020/04/26 11:03:38 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

void	verif_path_no(t_parsing *pars, char *path)
{
	pars->ptr_no = mlx_xpm_file_to_image(pars->mlx, path,
	&pars->tex_height, &pars->tex_wight);
	if (pars->ptr_no == NULL)
		error_informations(pars);
	pars->addr_no = mlx_get_data_addr(pars->ptr_no, &pars->bits_per_pixel_no,
	&pars->line_length_no, &pars->endian_no);
}

void	verif_path_so(t_parsing *pars, char *path)
{
	pars->ptr_so = mlx_xpm_file_to_image(pars->mlx, path,
	&pars->tex_height, &pars->tex_wight);
	if (pars->ptr_so == NULL)
		error_informations(pars);
	pars->addr_so = mlx_get_data_addr(pars->ptr_so, &pars->bits_per_pixel_so,
	&pars->line_length_so, &pars->endian_so);
}

void	verif_path_we(t_parsing *pars, char *path)
{
	pars->ptr_we = mlx_xpm_file_to_image(pars->mlx, path,
	&pars->tex_height, &pars->tex_wight);
	if (pars->ptr_we == NULL)
		error_informations(pars);
	pars->addr_we = mlx_get_data_addr(pars->ptr_we, &pars->bits_per_pixel_we,
	&pars->line_length_we, &pars->endian_we);
}

void	verif_path_ea(t_parsing *pars, char *path)
{
	pars->ptr_ea = mlx_xpm_file_to_image(pars->mlx, path,
	&pars->tex_height, &pars->tex_wight);
	if (pars->ptr_ea == NULL)
		error_informations(pars);
	pars->addr_ea = mlx_get_data_addr(pars->ptr_ea, &pars->bits_per_pixel_ea,
	&pars->line_length_ea, &pars->endian_ea);
}

void	verif_path_s(t_parsing *pars, char *path)
{
	pars->ptr_s = mlx_xpm_file_to_image(pars->mlx, path,
	&pars->tex_height, &pars->tex_wight);
	if (pars->ptr_s == NULL)
		error_informations(pars);
	pars->addr_s = mlx_get_data_addr(pars->ptr_s, &pars->bits_per_pixel_s,
	&pars->line_length_s, &pars->endian_s);
}
