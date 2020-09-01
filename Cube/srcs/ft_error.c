/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:05:54 by pacorrei          #+#    #+#             */
/*   Updated: 2020/01/08 00:32:10 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

void    error_informations(t_parsing *pars)
{
    ft_putstr("Error wrong informations");
    free_all(pars);
    exit(1);
}

void    error_malloc(t_parsing *pars)
{
    ft_putstr("Error malloc fail");
    free_all(pars);
    exit(1);
}

void    error_miss_informations(t_parsing *pars)
{
    ft_putstr("Error miss informations");
    free_all(pars);
    exit(1);
}

void    error_argument()
{
    ft_putstr("Error wrong argument");
    exit(1);
}

void    error_read_file(t_parsing *pars)
{
    ft_putstr("Error failed read file");
    free_all(pars);
    exit(1);
}

void    error_bmp_file(t_parsing *pars)
{
    ft_putstr("Error failed create/write bmp file");
    free_all(pars);
    exit(1);
}