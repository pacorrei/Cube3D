/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:05:54 by pacorrei          #+#    #+#             */
/*   Updated: 2020/01/08 00:32:10 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_cube.h"

void	free_char_double(char **str)
{
	int i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str[i]);
	free(str);
}

void	free_all(t_parsing *pars)
{
	if (pars->info != NULL)
		free_char_double(pars->info);
	if (pars->path_txt_no != NULL)
		free(pars->path_txt_no);
	if (pars->path_txt_so != NULL)
		free(pars->path_txt_so);
	if (pars->path_txt_we != NULL)
		free(pars->path_txt_we);
	if (pars->path_txt_ea != NULL)
		free(pars->path_txt_ea);
	if (pars->path_txt_s != NULL)
		free(pars->path_txt_s);
}