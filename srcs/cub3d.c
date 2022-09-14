/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 14:11:20 by abahmani          #+#    #+#             */
/*   Updated: 2022/09/14 19:22:19 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    win(t_win mlx)
{

    mlx.mlx = mlx_init();
    mlx.mlx_win = mlx_new_window(mlx.mlx, 1080, 720, "cub3d");
    mlx_loop(mlx.mlx);
}

int	main(int ac, char **av)
{
    (void)ac;
    (void)av;
    t_win mlx;
    int x, y;
    y = 0;
    
    mlx.mlx = mlx_init();
    mlx.mlx_img = mlx_new_image(mlx.mlx, 1080, 720);
    mlx.
    mlx.mlx_win = mlx_new_window(mlx.mlx, 1080, 720, "cub3d");
    while (y < 720)
    {
        x = 0;
        while (x < 1080)
        {
            mlx_pixel_put(mlx.mlx, mlx.mlx_win, x, y, 0xDE3163);
            x++;
        }
        y++;
    }
    mlx_loop(mlx.mlx);
}