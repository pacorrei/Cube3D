/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:05:54 by pacorrei          #+#    #+#             */
/*   Updated: 2020/01/08 00:32:10 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

void	binary_shift(unsigned char *str, int value)
{
	str[0] = (unsigned char)(value);
	str[1] = (unsigned char)(value >> 8);
	str[2] = (unsigned char)(value >> 16);
	str[3] = (unsigned char)(value >> 24);
}

int		ft_write_in_file_header(int fd, int nbr, t_parsing *pars)
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
	binary_shift(header + 18, pars->res_x);
	binary_shift(header + 22, pars->res_y);
	header[27] = (unsigned char)(1);
	header[28] = (unsigned char)(24);
	return (!(write(fd, header, 54) < 0));
}

int		get_color(t_parsing *pars, int x, int y)
{
	if (x < 0 || y < 0)
		return (0x0);
	return (*(int*)(pars->addr + ((x + (y * pars->res_x)) *
	(pars->bits_per_pixel / 8))));
}

int 	get_empty_byte(int reste)
{
	if (reste == 1)
		return (0xFF0000);
	if (reste == 2)
		return (0x00FF00);
	if (reste == 3)
		return (0x0000FF);
	return (0);
}

int		ft_write_in_file_img(int fd, t_parsing *pars, int reste)
{
	int x;
	int y;
	int	color;

	y = pars->res_y;
	while (y > 0)
	{
		x = 0;
		while (x < pars->res_x)
		{
			color = get_color(pars, x, y);
			if (write(fd, &color, 3) < 0)
				return (0);
			x++;
		}
		if (reste != 0)
		{
			color = get_empty_byte(reste);
			if (write(fd, &color, reste) < 0)
				return (0);
		}
		y--;
	}
	return (1);
}

void	make_bmp(t_parsing *pars)
{
	int fd;
	int reste;

	reste = pars->res_x % 4;
	printf(" reste ;%d\n", reste);
	fd = open("cube.bmp", O_CREAT | O_TRUNC | O_RDWR, S_IRWXU |
	S_IRWXG | S_IRWXO);
	if (fd == -1)
		error_bmp_file(pars);
	ft_write_in_file_header(fd, 54 + (pars->res_x * pars->res_y), pars);
	if (ft_write_in_file_img(fd, pars, reste) == 0)
		error_write_bmp(pars);
	free_all(pars);
	close(fd);
	exit(0);
}
