/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2020/04/26 11:03:38 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

void	vector_dir_value2(t_parsing *pars)
{
	if (pars->pos_player == 'N')
	{
		pars->dirx = 1;
		pars->diry = 0;
		pars->planex = 0;
		pars->planey = 0.66;
	}
	if (pars->pos_player == 'S')
	{
		pars->dirx = -1;
		pars->diry = 0;
		pars->planex = 0;
		pars->planey = -0.66;
	}
}

void	vector_dir_value(t_parsing *pars)
{
	if (pars->pos_player == 'W')
	{
		pars->dirx = 0;
		pars->diry = -1;
		pars->planex = 0.66;
		pars->planey = 0;
	}
	if (pars->pos_player == 'E')
	{
		pars->dirx = 0;
		pars->diry = 1;
		pars->planex = -0.66;
		pars->planey = 0;
	}
	vector_dir_value2(pars);
}

char	*get_addr_tex(t_parsing *pars)
{
	if (pars->side == 0)
	{
		if (pars->raydirx < 0)
			return (pars->addr_so);
		else
			return (pars->addr_no);
	}
	else
	{
		if (pars->raydiry < 0)
			return (pars->addr_we);
		else
			return (pars->addr_ea);
	}
}

int		get_line_length_tex(t_parsing *pars)
{
	if (pars->side == 0)
	{
		if (pars->raydirx < 0)
			return (pars->line_length_so);
		else
			return (pars->line_length_no);
	}
	else
	{
		if (pars->raydiry < 0)
			return (pars->line_length_we);
		else
			return (pars->line_length_ea);
	}
}

int		main(int ac, char **av)
{
	int			fd;
	t_parsing	pars;

	intit_struct_pars(&pars);
	pars.mlx = mlx_init();
	pars.tex_height = 64;
	pars.tex_wight = 64;
	main_verif_argument(&pars, av, ac);
	fd = open(av[1], O_RDONLY);
	recup_file(fd, &pars);
	close(fd);
	vector_dir_value(&pars);
	pars.z_buffer = malloc(sizeof(double) * (pars.res_x + 1));
	pars.z_buffer[pars.res_x] = '\0';
	if (pars.save == 0)
		pars.win = mlx_new_window(pars.mlx, pars.res_x, pars.res_y, "Cube3D");
	pars.img = mlx_new_image(pars.mlx, pars.res_x, pars.res_y);
	pars.addr = mlx_get_data_addr(pars.img, &pars.bits_per_pixel,
	&pars.line_length, &pars.endian);
	raycasting(&pars);
	mlx_loop_hook(pars.mlx, key_action, &pars);
	mlx_hook(pars.win, 2, 1L << 0, key_pressed, &pars);
	mlx_hook(pars.win, 3, 1L << 1, key_release, &pars);
	mlx_hook(pars.win, 33, 1L << 17, window_action, &pars);
	mlx_loop(pars.mlx);
}
