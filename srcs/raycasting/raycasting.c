/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 04:06:55 by abahmani          #+#    #+#             */
/*   Updated: 2022/10/15 17:59:54 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw(t_engine *eng)
{
	int	y;
	int	x;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			eng->mlx_data->data.data[y * SCREEN_WIDTH + x]
				= eng->mlx_data->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(eng->mlx_data->mlx, eng->mlx_data->mlx_win,
		eng->mlx_data->data.img, 0, 0);
}

void	ceiling_or_floor(t_engine *eng, int x, int q)
{
	int	i;
	int	y;

	i = 0;
	if (q == 0)
	{
		while (i < eng->cal->draw_start)
		{
			eng->mlx_data->buf[i][x] = eng->map_data->ceiling_rgb.color;
			eng->mlx_data->re_buf = 1;
			i++;
		}
	}
	else
	{
		y = eng->cal->draw_end;
		while (y < SCREEN_HEIGHT)
		{
			eng->mlx_data->buf[y]
			[x] = eng->map_data->floor_rgb.color;
			eng->mlx_data->re_buf = 1;
			y++;
		}
	}
}

void	init_var(t_engine *eng, int x)
{
	(void)x;
	eng->cal->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	eng->cal->ray_dir_x = eng->map_data->player.dir_x
		+ eng->map_data->player.plane_x * eng->cal->camera_x;
	eng->cal->ray_dir_y = eng->map_data->player.dir_y
		+ eng->map_data->player.plane_y * eng->cal->camera_x;
	eng->cal->map_x = (int)eng->map_data->player.pos_x;
	eng->cal->map_y = (int)eng->map_data->player.pos_y;
	eng->cal->delta_dist_x = fabs(1 / eng->cal->ray_dir_x);
	eng->cal->delta_dist_y = fabs(1 / eng->cal->ray_dir_y);
	eng->cal->hit = 0;
}

int	la_croix(t_engine *engine)
{
	ft_destroy_mlx(engine->mlx_data);
	clear(engine->garbage_coll);
	exit(0);
}

void	play(t_engine *eng)
{
	eng->mlx_data->mlx = mlx_init();
	display_tab(eng->map_data->map);
	init_perso(eng);
	eng->map_data->map[(int)eng->map_data->player.pos_y]
	[(int)eng->map_data->player.pos_x] = '0';
	exec_load(eng);
	eng->mlx_data->re_buf = 0;
	eng->mlx_data->mlx_win = mlx_new_window(eng->mlx_data->mlx,
			SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	eng->mlx_data->data.img = mlx_new_image(eng->mlx_data->mlx, 1080, 720);
	eng->mlx_data->data.data = (int *)mlx_get_data_addr(eng->mlx_data->data.img,
			&eng->mlx_data->data.bpp, &eng->mlx_data->data.line_length,
			&eng->mlx_data->data.endian);
	eng->mlx_data->up = 0;
	eng->mlx_data->down = 0;
	eng->mlx_data->right_pers = 0;
	eng->mlx_data->left_pers = 0;
	eng->mlx_data->left = 0;
	eng->mlx_data->right = 0;
	mlx_hook(eng->mlx_data->mlx_win, 2, 1L << 0, &key_press, eng);
	mlx_hook(eng->mlx_data->mlx_win, 3, 1L << 1, &key_release, eng);
	mlx_hook(eng->mlx_data->mlx_win, 17, 0, &la_croix, eng);
	mlx_loop_hook(eng->mlx_data->mlx, &get_move, eng);
	mlx_loop(eng->mlx_data->mlx);
}
