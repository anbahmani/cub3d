/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 14:11:20 by abahmani          #+#    #+#             */
/*   Updated: 2022/09/26 21:00:33 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


void    win(t_win mlx)
{

    mlx.mlx = mlx_init();
    mlx.mlx_win = mlx_new_window(mlx.mlx, 1080, 720, "cub3d");
    mlx_loop(mlx.mlx);
}

void	my_mlx_pixel_put(t_win *mlx, int x, int y, int color)
{
	char	*dst;
 
	dst = mlx->data.addr + (y * mlx->data.line_length + x * (mlx->data.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main_loop(t_win *mlx)
{
    mlx->data.img = mlx_new_image(mlx->mlx, 1920, 1080);
    mlx->data.addr = mlx_get_data_addr(mlx->data.img, &mlx->data.bits_per_pixel, &mlx->data.line_length, &mlx->data.endian);
	calcul(mlx);
    mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->data.img, 0, 0);
    mlx_destroy_image(mlx->mlx, mlx->data.img);
	return (0);
}


char    to_lower(char c)
{
    if (c >= 'A' && c <= 'Z')
        return (c + ('a' - 'A'));
    return (c);
}
 
int     get_digit(char c, int digits_in_base)
{
    int max_digit;
    if (digits_in_base <= 10)
        max_digit = digits_in_base + '0';
    else
        max_digit = digits_in_base - 10 + 'a';
 
    if (c >= '0' && c <= '9' && c <= max_digit)
        return (c - '0');
    else if (c >= 'a' && c <= 'f' && c <= max_digit)
        return (10 + c - 'a');
    else
        return (-1);
}
 
int     ft_atoi_base(const char *str, int str_base)
{
    int result = 0;
    int sign = 1;
    int digit;
 
    if (*str == '-')
    {
        sign = -1;
        ++str;
    }
 
    while ((digit = get_digit(to_lower(*str), str_base)) >= 0)
    {
        result = result * str_base;
        result = result + (digit * sign);
        ++str;
    }
    return (result);
}


char int_to_hexa(int nb)
{
    char *base;
    char color;
    
    base = malloc(sizeof(char) * 16);
    base = "0123456789ABCDEF";
    color = base[nb % 16];
    free(base);
    return (color);
}

int rgb_to_hexa(t_rgb rgb)
{
    char hexa[6];
    int x = rgb.red;
    int y = rgb.green;
    int z = rgb.blue;
    
    
    hexa[0] = int_to_hexa(x/16);
    hexa[1] = int_to_hexa(x);
    hexa[2] = int_to_hexa(y/16);
    hexa[3] = int_to_hexa(y);
    hexa[4] = int_to_hexa(z/16);
    hexa[5] = int_to_hexa(z);
    hexa[6] = '\0';
    
    return(ft_atoi_base(hexa, 16));
}

int	main(int ac, char **av)
{
    t_win mlx;
    t_map_data data;
    (void)ac;
    (void)av;


    mlx.mlx = mlx_init();
    mlx.perso.posX = 12;
	mlx.perso.posY = 5;
	mlx.perso.dirX = -1;
	mlx.perso.dirY = 0;
	mlx.perso.planeX = 0;
	mlx.perso.planeY = 0.66;
    mlx.perso.moveSpeed = 0.17;
	mlx.perso.rotSpeed = 0.14;

    rgb_to_hexa(data->floor_rgb);
	mlx.mlx_win = mlx_new_window(mlx.mlx, screenWidth, screenHeight, "cub3d");
   // mlx.data.img = mlx_new_image(mlx.mlx, 1920, 1080);
    //mlx.data.addr = mlx_get_data_addr(mlx.data.img, &mlx.data.bits_per_pixel, &mlx.data.line_length, &mlx.data.endian);

    mlx_loop_hook(mlx.mlx, &main_loop, &mlx);
    mlx_hook(mlx.mlx_win, 2, 1L << 0, &key_press, &mlx);
    mlx_hook(mlx.mlx_win, 2, 1L << 0, &key_press, &mlx);
    
    mlx_loop(mlx.mlx);
}