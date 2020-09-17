/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:05:54 by pacorrei          #+#    #+#             */
/*   Updated: 2020/01/08 00:32:10 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

void	error_informations(t_parsing *pars)
{
	ft_putstr("Error\nwrong informations");
	free_all(pars);
	exit(1);
}

void	error_malloc(t_parsing *pars)
{
	ft_putstr("Error\nmalloc fail");
	free_all(pars);
	exit(1);
}
