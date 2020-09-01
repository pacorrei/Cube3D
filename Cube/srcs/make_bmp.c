#include "ft_cube.h"


void	write_pixel_color(t_parsing *pars, int fd, int reste)
{
	int x;
	int y;
	int verif;

	y = pars->w;
	while (y > 0)
	{
		x = 0;
		verif = 1;
		ft_putchar('a');
		while (x < pars->h)
		{
			if (reste != 0 && verif == 1)
		{
			write(fd, "\0", reste);
			verif = 0;
		}
			ft_putchar('b');
			pars->alpha = pars->addr [(x * 4 + y * pars->line_length) + 0];
			write(fd, &pars->alpha, 1);
			ft_putchar('c');
			pars->red = pars->addr [(x * 4 + y * pars->line_length) + 1];
			write(fd, &pars->red, 1);
			pars->green = pars->addr [(x * 4 + y * pars->line_length) + 2];
			write(fd, &pars->green, 1);
			pars->blue = pars->addr [(x * 4 + y * pars->line_length) + 3];
			write(fd, &pars->blue, 1);
			x++;
		}
		y--;
	}
}

void	write_info_header(t_parsing *pars, int fd, int reste)
{
	int hsize;
	int plane;
	int color;
	int	isize;
	int nbcolor;

	hsize = 40;
	plane = 1;
	color = 32;
	isize = (pars->h * (pars->w + reste)) * 4;
	nbcolor = 0;
	write(fd, &hsize, 4);
	write(fd, &pars->w + reste, 4);
	write(fd, &pars->h, 4);
	write(fd, &plane, 2);
	write(fd, &color, 2);
	write(fd, "\0\0\0\0", 4);
	write(fd, &isize, 4);
	write(fd, &pars->w, 4);
	write(fd, &pars->h, 4);
	write(fd, &nbcolor, 4);
  	write(fd, &nbcolor, 4);
}

void	write_header(t_parsing *pars, int fd, int reste)
{
	int fsize;
	int toto = 14 + 40;

	fsize = 14 + 40 + ((pars->h * (pars->w + reste)) * 4);
	write(fd, "BM", 2);
	write(fd, &fsize, 4);
	//printf("decimal %d hexa %x\n", fsize, fsize);
	write(fd, "\0\0\0\0", 4);
	write(fd, &toto, 4);
}

void	make_bmp(t_parsing *pars)
{
	int fd;
	int reste;

	reste = 0;
	fd = open("cube.bmp", O_CREAT | O_TRUNC | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd == -1)
		error_bmp_file(pars);
	//printf(" fd ;%d x : %d y : %d\n", fd, pars->res_x, pars->res_y);
	if (pars->res_x % 4 != 0)
		reste = pars->res_x % 4;
	ft_putchar('1');
	write_header(pars, fd, reste);
	ft_putchar('2');
	write_info_header(pars, fd, reste);
	ft_putchar('3');
	write_pixel_color(pars, fd, reste);
	ft_putchar('4');
	close(fd);
}