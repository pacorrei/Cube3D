/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cube.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 13:43:56 by pacorrei          #+#    #+#             */
/*   Updated: 2020/08/20 17:37:18 by user42           ###   ########.fr       */
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
    int     screen_x;
    int     screen_y;
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
    int     key;
    int     side;
    int     lineHeight;
    int     drawStart;
    int     drawEnd;
    int     nb_sprite;
    int     **pos_sprite;
    int     *sprite_dist;
    int     *sprite_order;
    double     *z_buffer;
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    void    *ptr_no;
    void    *ptr_so;
    void    *ptr_ea;
    void    *ptr_we;
    void    *ptr_s;
	char    *addr_no;
    char    *addr_so;
    char    *addr_ea;
    char    *addr_we;
    char    *addr_s;
    char    *addr_tex;
    int		line_length_tex;
	int		line_length_no;
    int		line_length_so;
    int		line_length_ea;
    int		line_length_we;
    int		line_length_s;
	int		bits_per_pixel_no;
    int		bits_per_pixel_so;
    int		bits_per_pixel_ea;
    int		bits_per_pixel_we;
    int		bits_per_pixel_s;
	int		endian_no;
    int		endian_so;
    int		endian_ea;
    int		endian_we;
    int		endian_s;
    unsigned char   alpha;
    unsigned char   red;
    unsigned char   green;
    unsigned char   blue;
    int     tex_height;
    int     tex_wight;
    int     tex_line_lenght;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     save;
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
void    sort_sprites(t_parsing *pars);
void    find_sprite_pos(t_parsing *pars);
void    make_bmp(t_parsing *pars);
void    error_bmp_file(t_parsing *pars);


#endif