/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 14:11:20 by abahmani          #+#    #+#             */
/*   Updated: 2022/09/21 17:49:01 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#define screenWidth 1920
#define screenHeight 1080

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

	return (0);
}

int	main(int ac, char **av)
{
    t_win mlx;
    (void)ac;
    (void)av;


    mlx.mlx = mlx_init();

    mlx.perso.posX = 12;
	mlx.perso.posY = 5;
	mlx.perso.dirX = -1;
	mlx.perso.dirY = 0;
	mlx.perso.planeX = 0;
	mlx.perso.planeY = 0.66;
    mlx.perso.moveSpeed = 0.05;
	mlx.perso.rotSpeed = 0.05;

	mlx.mlx_win = mlx_new_window(mlx.mlx, screenWidth, screenHeight, "cub3d");
   // mlx.data.img = mlx_new_image(mlx.mlx, 1920, 1080);
    //mlx.data.addr = mlx_get_data_addr(mlx.data.img, &mlx.data.bits_per_pixel, &mlx.data.line_length, &mlx.data.endian);

    mlx_loop_hook(mlx.mlx, &main_loop, &mlx);
    mlx_key_~hook(mlx.mlx_win, &key_press, &mlx);
    
    mlx_loop(mlx.mlx);
}