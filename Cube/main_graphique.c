#include <mlx.h>

/*
void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int             main(void)
{
    void    *mlx;
    void    *mlx_win;
    int     y;
    int     i;
    int     x;
    int     k;
    int    color;
    t_data  img;

    y = 100;
    i = 50;
    color = 0;
    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 1000, 1000, "Hello world!");
    img.img = mlx_new_image(mlx, 1000, 1000);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
    while (y < 150)
    {   
        x = 500 - i;
        k = x;
        while (x - i <= k + i)
        {
            my_mlx_pixel_put(&img, x, y, 0x00FFF000 + color);
            x++;
        }
        color = color + 2;
        i++;
        y++;
    }
    while (y < 200)
    {   
        x = 500 - i;
        k = x;
        while (x - i <= k + i)
        {
            my_mlx_pixel_put(&img, x, y, 0x00FFF000 + color);
            x++;
        }
        color = color + 2;
        y++;
    }
     while (y < 250)
    {   
        x = 500 - i;
        k = x;
        while (x - i <= k + i)
        {
            my_mlx_pixel_put(&img, x, y, 0x00FFF000 + color);
            x++;
        }
        color = color + 2;
        i--;
        y++;
    }
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
}*/

typedef struct  s_data {
    void        *mlx;
    void        *win;
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
    int         haut;
    int         bas;
    int         droite;
    int         gauche;
}               t_data;

void            my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
    char    *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int             close(int keycode, t_data *img)
{
    if (keycode == 65307)
        mlx_destroy_window(img->mlx, img->win);
    if (keycode == 113)
    {
        img->droite--;
        img->gauche--;
    }
    if (keycode == 115)
    {
        img->haut++;
        img->bas++;
    }
    if (keycode == 100)
    {
        img->gauche++;
        img->droite++;
    }
    if (keycode == 122)
    {
        img->bas--;
        img->haut--;
    }
    return (0);
}

int     render_next_frame(t_data *img)
{
    int y;
    int x;
    int a;
    int b;
    int c;

    c = 0;
    y = img->haut;
    while (c < y)
    {
        a = 0;
        while (a <= 1000)
        {
            my_mlx_pixel_put(img, a, c, 0x00000000);
            a++;
        }
        c++;
    }
    while (y < img->bas)
    {
        x = img->gauche;
        a = 0;
        while (a < x)
        {
            my_mlx_pixel_put(img, a, y, 0x00000000);
            a++;
        }
        while (x < img->droite)
        {
            my_mlx_pixel_put(img, x, y, 0x00FFF000);
            x++;
        }
        b = x + 1;
        while (b <= 1000)
        {
            my_mlx_pixel_put(img, b, y, 0x00000000);
            b++;
        }
        y++;
    }
    c = img->bas;
    while (c <= 1000)
    {
        a = 0;
        while (a <= 1000)
        {
            my_mlx_pixel_put(img, a, c, 0x00000000);
            a++;
        }
        c++;
    }
    mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
    return (0);
}

int     main(void)
{
    int x;
    int y;
    t_data  img;

    img.haut = 100;
    img.bas = 500;
    img.droite = 500;
    img.gauche = 100;
    img.mlx = mlx_init();
    img.win = mlx_new_window(img.mlx, 1000, 1000, "Hello world!");
    img.img = mlx_new_image(img.mlx, 1000, 1000);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    /*y = 100;
    while (y < 500)
    {
        x = 100;
        while (x < 500)
        {
            my_mlx_pixel_put(&img, x, y, 0x00FFF000);
            x++;
        }
        y++;
    }*/
    mlx_loop_hook(img.mlx, render_next_frame, &img);
    mlx_hook(img.win, 2, 1L<<0, close, &img);
    mlx_loop(img.mlx);
}
