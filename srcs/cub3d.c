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
#define screenWidth 1920
#define screenHeight 1080
#define texWidth 64
#define texHeight 64

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
    //mlx->data.img = mlx_new_image(mlx->mlx, 1920, 1080);
    //mlx->data.addr = mlx_get_data_addr(mlx->data.img, &mlx->data.bits_per_pixel, &mlx->data.line_length, &mlx->data.endian);
	calcul(mlx);
    draw(mlx);
    //mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->data.img, 0, 0);
    //mlx_destroy_image(mlx->mlx, mlx->data.img);
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
    mlx.perso.moveSpeed = 0.17;
	mlx.perso.rotSpeed = 0.14;

    for (int i = 0; i < screenHeight; i++)
	{
		for (int j = 0; j < screenWidth; j++)
		{
			mlx.buf[i][j] = 0;
		}
	}

	if (!(mlx.texture = (int **)malloc(sizeof(int *) * 8)))
		return (-1);
	for (int i = 0; i < 8; i++)
	{
		if (!(mlx.texture[i] = (int *)malloc(sizeof(int) * (texHeight * texWidth))))
			return (-1);
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < texHeight * texWidth; j++)
		{
			mlx.texture[i][j] = 0;
		}
	}
	fprintf(stderr, "lalalalal\n");
	load_texture(&mlx);
	mlx.mlx_win = mlx_new_window(mlx.mlx, screenWidth, screenHeight, "cub3d");
    //mlx.data.img = mlx_new_image(mlx.mlx, 1920, 1080);
   // mlx.data.data = (int *)mlx_get_data_addr(mlx.data.img, &mlx.data.bits_per_pixel, &mlx.data.line_length, &mlx.data.endian);
    mlx_loop_hook(mlx.mlx, &main_loop, &mlx);
    mlx_hook(mlx.mlx_win, 2, 1L << 0, &key_press, &mlx);
    
    mlx_loop(mlx.mlx);
}