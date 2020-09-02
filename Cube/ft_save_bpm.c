/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_bpm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 07:40:53 by user42            #+#    #+#             */
/*   Updated: 2020/06/07 10:29:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	binary_shift(unsigned char *str, int value)
{
	str[0] = (unsigned char)(value);
	str[1] = (unsigned char)(value >> 8);
	str[2] = (unsigned char)(value >> 16);
	str[3] = (unsigned char)(value >> 24);
}

int		ft_write_in_file_header(int n, int nbr, t_win *win)
{
	unsigned char	header[54];
	int				i;

	i = 0;
	while (i < 54)
		header[i++] = (unsigned char)0;
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	binary_shift(header + 2, nbr);
	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)(40);
	binary_shift(header + 18, win->map->x_res);
	binary_shift(header + 22, win->map->y_res);
	header[27] = (unsigned char)(1);
	header[28] = (unsigned char)(24);
	return (!(write(n, header, 54) < 0));
}

int		get_color(t_win *win, int x, int y)
{
	return (*(int*)(win->addr + ((x + (y * win->map->x_res)) *
	(win->bits_per_pixel / 8))));
}

int		ft_write_in_file_img(int n, t_win *win)
{
	int x;
	int y;
	int	color;

	y = win->map->y_res;
	while (y > 0)
	{
		x = 0;
		while (x < win->map->x_res)
		{
			color = get_color(win, x, y);
			if (write(n, &color, 3) < 0)
				return (0);
			x++;
		}
		y--;
	}
	return (1);
}

void	ft_save_bmp(t_win *win)
{
	int n;

	n = open("image.bmp", O_WRONLY | O_CREAT,
	S_IWUSR | S_IRUSR | S_IROTH | S_IRGRP);
	ft_write_in_file_header(n, 54 + (win->map->x_res * win->map->y_res), win);
	if (ft_write_in_file_img(n, win) == 0)
		ft_error("Error write");
	if (n < 0)
		ft_error("Error open");
	close(n);
}
