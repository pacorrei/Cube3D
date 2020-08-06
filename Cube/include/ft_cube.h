/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cube.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 13:43:56 by pacorrei          #+#    #+#             */
/*   Updated: 2020/04/24 15:45:15 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUBE_H
# define FT_CUBE_H
# include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

typedef struct  s_parsing{
    char    **info;
    char    **worldMap;
    char    *path_txt_no;
    char    *path_txt_so;
    char    *path_txt_we;
    char    *path_txt_ea;
    char    *path_txt_s;
    char    pos_player;
    int     res_x;
    int     res_y;
    int     r_ceil;
    int     g_ceil;
    int     b_ceil;
    int     r_floor;
    int     g_floor;
    int     b_floor;
    double  dirX;
    double  dirY;
    double  posX;
    double  posY;
    double  planeX;
    double  planeY;
    int     x;
    int     w;
    int     h;
    double  cameraX;
    double  rayDirX;
    double  rayDirY;
    int     mapX;
    int     mapY;
    double  sideDistX;
    double  sideDistY;
    double  deltaDistX;
    double  deltaDistY;
    double  perpWallDist;
    double  moveSpeed;
    double  rotSpeed;
    double  oldDirX;
    double  oldPlaneX;
    int     stepX;
    int     stepY;
    int     hit;
    int     side;
    int     lineHeight;
    int     drawStart;
    int     drawEnd;
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}                   t_parsing;

void	free_char_double(char **str);
void    ft_putchar(char c);
void    recup_file(int fd, t_parsing *pars);
void    intit_struct_pars(t_parsing *pars);
void	free_all(t_parsing *pars);
void    error_informations(t_parsing *pars);
void    error_argument();
void    error_read_file(t_parsing *pars);
void	ft_putstr(char *str);
void    find_informations(t_parsing *pars);
void    error_miss_informations(t_parsing *pars);
void    error_malloc(t_parsing *pars);
int		ft_atoi(char *str);
void    verif_argument(char *str);
void    verif_argument_save(char *str);
int		find_nb(t_parsing *pars, int i, int j);
void    identifiers_r(t_parsing *pars, int i, int j);
void    identifiers_f(t_parsing *pars, int i, int j);
void    identifiers_c(t_parsing *pars, int i, int j);
void    identifiers_no(t_parsing *pars, int i, int j);
void    identifiers_so(t_parsing *pars, int i, int j);
void    identifiers_we(t_parsing *pars, int i, int j);
void    identifiers_ea(t_parsing *pars, int i, int j);
void    identifiers_s(t_parsing *pars, int i, int j);
void    verif_valid_map(t_parsing *pars, int i, int j);
void    verif_close_map(t_parsing *pars, int i, int j);
void    raycasting(t_parsing *pars);


#endif