/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 04:06:55 by abahmani          #+#    #+#             */
/*   Updated: 2022/10/14 20:35:10 by raaga            ###   ########.fr       */
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

void	init_side_dist(t_engine *eng)
{
	if (eng->cal->ray_dir_x < 0)
	{
		eng->cal->step_x = -1;
		eng->cal->side_dist_x = (eng->map_data->player.pos_x - eng->cal->map_x) * eng->cal->delta_dist_x;
	}
	else
	{
		eng->cal->step_x = 1;
		eng->cal->side_dist_x = (eng->cal->map_x + 1.0 - eng->map_data->player.pos_x) * eng->cal->delta_dist_x;
	}
	if (eng->cal->ray_dir_y < 0)
	{
		eng->cal->step_y = -1;
		eng->cal->side_dist_y = (eng->map_data->player.pos_y - eng->cal->map_y) * eng->cal->delta_dist_y;
	}
	else
	{
		eng->cal->step_y = 1;
		eng->cal->side_dist_y = (eng->cal->map_y + 1.0 - eng->map_data->player.pos_y) * eng->cal->delta_dist_y;
	}
	wall_detect(eng);
}

int calcul(t_engine *eng, int x)
{	
	while (x < SCREEN_WIDTH)
	{
		init_var(eng, x);
		init_side_dist(eng);
		eng->cal->line_height = (int)(SCREEN_HEIGHT / eng->cal->perp_wall_dist);
		eng->cal->draw_start = -(eng->cal->line_height) / 2 + SCREEN_HEIGHT / 2;
		if(eng->cal->draw_start < 0)
			eng->cal->draw_start = 0;
		eng->cal->draw_end = eng->cal->line_height / 2 + SCREEN_HEIGHT / 2;
		if(eng->cal->draw_end >= SCREEN_HEIGHT)
			eng->cal->draw_end = SCREEN_HEIGHT - 1;
		eng->cal->tex_num = eng->map_data->map[eng->cal->map_y][eng->cal->map_x] - 48;
		eng->cal->tex_x = (int)(eng->cal->wall_x * (double)TEX_WIDTH);
		if (eng->cal->side == 0 && eng->cal->ray_dir_x > 0)
			eng->cal->tex_x = TEX_WIDTH - eng->cal->tex_x - 1;
		if (eng->cal->side == 1 && eng->cal->ray_dir_y < 0)
			eng->cal->tex_y = TEX_WIDTH - eng->cal->tex_x - 1;
		eng->cal->step = 1.0 * TEX_HEIGHT / eng->cal->line_height;
		eng->cal->tex_pos = (eng->cal->draw_start - SCREEN_HEIGHT / 2 + eng->cal->line_height / 2) * eng->cal->step;
		ceiling_or_floor(eng, x, 0);
		ceiling_or_floor(eng, x, 1);
		wall_draw(eng, x, eng->cal->draw_start, eng->cal->draw_end);
		x++;
	}
	return (0);
}

void	load_image(t_engine *eng, int *texture, char *path, t_data *data)
{
	int y;
	int x;

	y = 0;
	data->img = mlx_xpm_file_to_image(eng->mlx_data->mlx, path, &data->img_width, &data->img_height);
	data->data = (int *)mlx_get_data_addr(data->img, &data->bpp, &data->size_l, &data->endian);
	while (y < data->img_height)
	{
		x = 0;
		while (x < data->img_width)
		{
			texture[data->img_width * y + x] = data->data[data->img_width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(eng->mlx_data->mlx, data->img);
}

void	load_texture(t_engine *eng)
{
	t_data img;

	load_image(eng, eng->mlx_data->texture[0], eng->map_data->north_text, &img);
	load_image(eng, eng->mlx_data->texture[1], eng->map_data->south_text, &img);
	load_image(eng, eng->mlx_data->texture[2], eng->map_data->east_text, &img);
	load_image(eng, eng->mlx_data->texture[3], eng->map_data->west_text, &img);
}

int	key_press(int key, t_engine *engine)
{
	if (key == 119)
		engine->mlx_data->up = 1;
	if (key == 115)
		engine->mlx_data->down = 1;
	if (key == 100)
		engine->mlx_data->left_pers = 1;
	if (key == 97)
		engine->mlx_data->right_pers = 1;
	if (key == 65361)
		engine->mlx_data->right = 1;
	if (key == 65363)
		engine->mlx_data->left = 1;
	if (key == 65307)
	{
		ft_destroy_mlx(engine->mlx_data);
		clear(engine->garbage_coll);
		exit(0);
	}
	return (0);
}

int	la_croix(t_engine *engine)
{
	ft_destroy_mlx(engine->mlx_data);
	clear(engine->garbage_coll);
	exit(0);
}

int	key_release(int key, t_engine *eng)
{
	if (key == 119)
		eng->mlx_data->up = 0;
	if (key == 115)
		eng->mlx_data->down = 0;
	if (key == 100)
		eng->mlx_data->left_pers = 0;
	if (key == 97)
		eng->mlx_data->right_pers = 0;
	if (key == 65361)
		eng->mlx_data->right = 0;
	if (key == 65363)
		eng->mlx_data->left = 0;
	return (0);
}

void	exec_load(t_engine *eng)
{
	int i;
	int j;

	i = -1;
	while (++i < SCREEN_HEIGHT)
	{
		j = -1;
		while (++j < SCREEN_WIDTH)
			eng->mlx_data->buf[i][j] = 0;
	}
	eng->mlx_data->texture = (int **)ft_malloc(sizeof(int *) * 4, eng->garbage_coll);
	if (!(eng->mlx_data->texture))
		quit_error(MALLOC_ERROR, eng->garbage_coll);
	i = -1;
	while (++i < 4)
	{
		eng->mlx_data->texture[i] = (int *)ft_malloc(sizeof(int) * (TEX_HEIGHT * TEX_WIDTH), eng->garbage_coll);
		if (!eng->mlx_data->texture[i])
			quit_error(MALLOC_ERROR, eng->garbage_coll);
	}
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < TEX_HEIGHT * TEX_WIDTH)
			eng->mlx_data->texture[i][j] = 0;
	}
	load_texture(eng);
}

void	play(t_engine *eng)
{
	eng->mlx_data->mlx = mlx_init();
	display_tab(eng->map_data->map);
	init_perso(eng);
	eng->map_data->map[(int)eng->map_data->player.pos_y][(int)eng->map_data->player.pos_x] = '0';
	exec_load(eng);
	eng->mlx_data->re_buf = 0;
	eng->mlx_data->mlx_win = mlx_new_window(eng->mlx_data->mlx, SCREEN_WIDTH , SCREEN_HEIGHT , "cub3d");
    eng->mlx_data->data.img = mlx_new_image(eng->mlx_data->mlx, 1080, 720);
    eng->mlx_data->data.data = (int *)mlx_get_data_addr(eng->mlx_data->data.img, &eng->mlx_data->data.bpp, &eng->mlx_data->data.line_length, &eng->mlx_data->data.endian);
	eng->mlx_data->up = 0;
	eng->mlx_data->down = 0;
	eng->mlx_data->right_pers = 0;
	eng->mlx_data->left_pers = 0;
	eng->mlx_data->left = 0;
	eng->mlx_data->right = 0;
	mlx_hook(eng->mlx_data->mlx_win, 2, 1L << 0, &key_press,  eng);
    mlx_hook(eng->mlx_data->mlx_win, 3, 1L << 1, &key_release, eng);
	mlx_hook(eng->mlx_data->mlx_win, 17, 0, &la_croix, eng);
	mlx_loop_hook(eng->mlx_data->mlx, &get_move, eng);
    mlx_loop(eng->mlx_data->mlx);
}