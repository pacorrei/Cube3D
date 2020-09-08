/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2020/04/26 11:03:38 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cube.h"

void	verif_argument(char *str)
{
	int i;
	int verif;

	i = 0;
	verif = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '.' && str[i + 1] == 'c' && str[i + 2] == 'u' &&
		str[i + 3] == 'b')
			verif = 1;
		i++;
	}
	if (verif == 0)
		error_argument();
}

void	verif_argument_save(char *str)
{
	int i;
	int verif;

	i = 0;
	verif = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '-' && str[i + 1] == '-' && str[i + 2] == 's' &&
		str[i + 3] == 'a' && str[i + 4] == 'v' && str[i + 5] == 'e')
			verif = 1;
		i++;
	}
	if (verif == 0)
		error_argument();
}

void	main_verif_argument(t_parsing *pars, char **av, int ac)
{
	if (ac == 1 || ac > 3)
		error_argument();
	verif_argument(av[1]);
	if (ac == 3)
	{
		verif_argument_save(av[2]);
		pars->save = 1;
	}
}
