/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 14:11:20 by abahmani          #+#    #+#             */
/*   Updated: 2022/09/28 19:32:45 by raaga            ###   ########.fr       */
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
	int	*dst;
 
	dst = mlx->data.data + (y * mlx->data.line_length + x * (mlx->data.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}



int	main(int ac, char **av)
{
    t_win mlx;
    (void)ac;
    (void)av;
    unsigned char tab[4] = {51, 87, 255, 0};
    mlx.color = *(unsigned int *)tab;

    mlx.mlx = mlx_init();

    mlx.perso.posX = 8;
	mlx.perso.posY = 2;
	mlx.perso.dirX = 0;
	mlx.perso.dirY = 1;
	mlx.perso.planeX = (0.66 * mlx.perso.dirY);
	mlx.perso.planeY = (0.66 * (-1 * mlx.perso.dirX));

	mlx.re_buf = 0;

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
	load_texture(&mlx);

	mlx.perso.moveSpeed = 0.17;
	mlx.perso.rotSpeed = 0.14;

	mlx.mlx_win = mlx_new_window(mlx.mlx, screenWidth, screenHeight, "cub3d");
    mlx.data.img = mlx_new_image(mlx.mlx, 1920, 1080);
    mlx.data.data = (int *)mlx_get_data_addr(mlx.data.img, &mlx.data.bits_per_pixel, &mlx.data.line_length, &mlx.data.endian);
    mlx_hook(mlx.mlx_win, 2, 1L << 0, &key_press, &mlx);
    mlx_hook(mlx.mlx_win, 3, 1L << 1, &key_release, &mlx);
	mlx_loop_hook(mlx.mlx, &main_loop, &mlx);
    mlx_loop(mlx.mlx);
}