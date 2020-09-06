/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 13:43:56 by pacorrei          #+#    #+#             */
/*   Updated: 2020/04/24 15:45:15 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

void	intit_struct_pars(t_parsing *pars)
{
	pars->info = NULL;
	pars->worldMap = NULL;
	pars->path_txt_no = NULL;
	pars->path_txt_so = NULL;
	pars->path_txt_we = NULL;
	pars->path_txt_ea = NULL;
	pars->path_txt_s = NULL;
	pars->nb_sprite = 0;
	pars->pos_sprite = NULL;
	pars->sprite_dist = NULL;
	pars->sprite_order = NULL;
	pars->save = 0;
	pars->screen_x = 0;
	pars->screen_y = 0;
}

void	ft_realloc_map(t_parsing *pars, char *line)
{
	char	**copy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (pars->info[i] != NULL)
		i++;
	copy = (char**)malloc(sizeof(char*) * (i + 2));
	copy[i + 1] = NULL;
	i = 0;
	while (pars->info[i] != NULL)
		copy[i++] = ft_strdup(pars->info[j++]);
	copy[i] = ft_strdup(line);
	free_char_double(pars->info);
	i = 0;
	while (copy[i] != NULL)
		i++;
	pars->info = (char**)malloc(sizeof(char*) * (i + 1));
	pars->info[i] = NULL;
	i = 0;
	j = 0;
	while (copy[i] != NULL)
		pars->info[i++] = ft_strdup(copy[j++]);
	free_char_double(copy);
}

void	recup_file(int fd, t_parsing *pars)
{
	char	*line;
	int		ret;

	pars->info = (char**)malloc(sizeof(char*) * 1);
	pars->info[0] = NULL;
	line = NULL;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		ft_realloc_map(pars, line);
		free(line);
	}
	if (ret == -1)
	{
		free(line);
		error_read_file(pars);
	}
	ft_realloc_map(pars, line);
	free(line);
	find_informations(pars);
}
