#include "ft_cube.h"

int	main(int ac, char **av)
{
	int fd;

	fd = open(av[1], O_RDONLY);
	if (ac == 1 || ac > 3)
		error_argument();
	verif_argument(av[1]);
	if (ac == 3)
		verif_argument_save(av[2]);
	recup_file(fd);

	return (0);
}
