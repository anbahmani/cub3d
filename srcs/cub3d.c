/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 14:11:20 by abahmani          #+#    #+#             */
/*   Updated: 2022/09/15 20:30:50 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    win(t_win mlx)
{

    mlx.mlx = mlx_init();
    mlx.mlx_win = mlx_new_window(mlx.mlx, 1080, 720, "cub3d");
    mlx_loop(mlx.mlx);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(int ac, char **av)
{
    (void)ac;
    (void)av;
    t_win mlx;
    int x, y;
    y = 0;
    
    mlx.mlx = mlx_init();
    mlx.mlx_win = mlx_new_window(mlx.mlx, 1080, 720, "cub3d");
    mlx.data.img = mlx_new_image(mlx.mlx, 1080, 720);
    mlx.data.addr = mlx_get_data_addr(mlx.data.img, &mlx.data.bits_per_pixel, &mlx.data.line_length, &mlx.data.endian);
    
    while (y < 720/2)
    {
        x = 0;
        while (x < 1080)
        {
            my_mlx_pixel_put(&mlx.data, x, y, 0xDE3163);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.data.img, 0, 0);
    mlx_destroy_image(mlx.mlx, mlx.data.img);
    mlx_loop(mlx.mlx);
}