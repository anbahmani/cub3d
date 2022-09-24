/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 14:11:20 by abahmani          #+#    #+#             */
/*   Updated: 2022/09/24 06:28:57 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

//function made for test - TODO : del before pushing for evaluation
void	display_tab(char **split)
{
	int i = 0;

	while (split[i])
	{
		printf("split[%d] = \t%s\n", i, split[i]);
		i++;
	}
}

//function made for test - TODO : del before pushing for evaluation
void display_data(t_map_data data)
{
	printf("NO ->%s\n", data.north_text);
	printf("SO ->%s\n", data.south_text);
	printf("EA ->%s\n", data.east_text);
	printf("WE ->%s\n", data.west_text);
	printf("C ->%d, %d, %d\n", data.ceiling_rgb.red, data.ceiling_rgb.green, data.ceiling_rgb.blue);
	printf("F ->%d, %d, %d\n", data.floor_rgb.red, data.floor_rgb.green, data.floor_rgb.blue);
}

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
    mlx_destroy_image(mlx->mlx, mlx->data.img);
	return (0);
}

int	main(int ac, char **av)
{
	t_engine	eng;

	eng.garbage_coll = malloc(sizeof(t_list));
	if (!eng.garbage_coll)
		quit_error(MALLOC_ERROR, eng.garbage_coll);
	eng.map_data = ft_malloc(sizeof(t_map_data), eng.garbage_coll);
	check_error(ac, av, eng.garbage_coll);
	get_file_data(av[1], eng.map_data, eng.garbage_coll);
	check_text_file_error(&eng);
	find_map(av[1], eng.map_data, eng.garbage_coll);
	eng.mlx_data = ft_malloc(sizeof(t_win), eng.garbage_coll);
	// mlx.data.img = mlx_new_image(mlx.mlx, 1920, 1080);
    //mlx.data.addr = mlx_get_data_addr(mlx.data.img, &mlx.data.bits_per_pixel, &mlx.data.line_length, &mlx.data.endian);
	mlx_loop_hook(eng.mlx_data->mlx, &main_loop, eng.mlx_data);
    mlx_hook(eng.mlx_data->mlx_win, 2, 1L << 0, &key_press, eng.mlx_data);
    mlx_hook(eng.mlx_data->mlx_win, 2, 1L << 0, &key_press, eng.mlx_data);
    mlx_loop(eng.mlx_data->mlx);
	
	/*
	display_tab(eng.map_data->map);
	display_data(*eng.map_data);
	*/
	
	
	
	clear(eng.garbage_coll);
	return (0);
}