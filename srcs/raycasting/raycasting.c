/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 04:06:55 by abahmani          #+#    #+#             */
/*   Updated: 2022/10/07 20:09:29 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main_loop(t_engine *eng)
{
	double	old_dir_x;
	double	old_plane_x;

	if (eng->mlx_data->up)
	{
		if (eng->map_data->map[(int)(eng->map_data->player.pos_y)][(int)(eng->map_data->player.pos_x + eng->map_data->player.dir_x * eng->map_data->player.move_speed)] == '0')
			eng->map_data->player.pos_x += eng->map_data->player.dir_x * eng->map_data->player.move_speed;
		if (eng->map_data->map[(int)(eng->map_data->player.pos_y + eng->map_data->player.dir_y * eng->map_data->player.move_speed)][(int)(eng->map_data->player.pos_x)] == '0')
			eng->map_data->player.pos_y += eng->map_data->player.dir_y * eng->map_data->player.move_speed;
	}
	if (eng->mlx_data->down)
	{
		if (eng->map_data->map[(int)(eng->map_data->player.pos_y)][(int)(eng->map_data->player.pos_x - eng->map_data->player.dir_x * eng->map_data->player.move_speed)] == '0')
			eng->map_data->player.pos_x -= eng->map_data->player.dir_x * eng->map_data->player.move_speed;
		if (eng->map_data->map[(int)(eng->map_data->player.pos_y - eng->map_data->player.dir_y * eng->map_data->player.move_speed)][(int)(eng->map_data->player.pos_x)] == '0')
			eng->map_data->player.pos_y -= eng->map_data->player.dir_y * eng->map_data->player.move_speed;
	}
	if (eng->mlx_data->right)
	{
		old_dir_x = eng->map_data->player.dir_x;
		eng->map_data->player.dir_x = eng->map_data->player.dir_x * cos(-eng->map_data->player.rot_speed) - eng->map_data->player.dir_y * sin(-eng->map_data->player.rot_speed);
		eng->map_data->player.dir_y = old_dir_x * sin(-eng->map_data->player.rot_speed) + eng->map_data->player.dir_y * cos(-eng->map_data->player.rot_speed);
		old_plane_x = eng->map_data->player.plane_x;
		eng->map_data->player.plane_x = eng->map_data->player.plane_x * cos(-eng->map_data->player.rot_speed) - eng->map_data->player.plane_y * sin(-eng->map_data->player.rot_speed);
		eng->map_data->player.plane_y = old_plane_x * sin(-eng->map_data->player.rot_speed) + eng->map_data->player.plane_y * cos(-eng->map_data->player.rot_speed);
	}
	if (eng->mlx_data->left)
	{
		old_dir_x = eng->map_data->player.dir_x;
		eng->map_data->player.dir_x = eng->map_data->player.dir_x * cos(eng->map_data->player.rot_speed) - eng->map_data->player.dir_y * sin(eng->map_data->player.rot_speed);
		eng->map_data->player.dir_y = old_dir_x * sin(eng->map_data->player.rot_speed) + eng->map_data->player.dir_y * cos(eng->map_data->player.rot_speed);
		old_plane_x = eng->map_data->player.plane_x;
		eng->map_data->player.plane_x = eng->map_data->player.plane_x * cos(eng->map_data->player.rot_speed) - eng->map_data->player.plane_y * sin(eng->map_data->player.rot_speed);
		eng->map_data->player.plane_y = old_plane_x * sin(eng->map_data->player.rot_speed) + eng->map_data->player.plane_y * cos(eng->map_data->player.rot_speed);
	}
	if (eng->mlx_data->right_pers)
	{
		if (eng->map_data->map[(int)(eng->map_data->player.pos_y)][(int)(eng->map_data->player.pos_x + eng->map_data->player.dir_y * eng->map_data->player.move_speed)] == '0')
				eng->map_data->player.pos_x +=  eng->map_data->player.dir_y * eng->map_data->player.move_speed;
		if (eng->map_data->map[(int)(eng->map_data->player.pos_y - eng->map_data->player.dir_x* eng->map_data->player.move_speed)][(int)(eng->map_data->player.pos_x)] == '0')
				eng->map_data->player.pos_y -=  eng->map_data->player.dir_x * eng->map_data->player.move_speed;
	}
	if (eng->mlx_data->left_pers)
	{
		if (eng->map_data->map[(int)(eng->map_data->player.pos_y)][(int)(eng->map_data->player.pos_x - eng->map_data->player.dir_y * eng->map_data->player.move_speed)] == '0')
				eng->map_data->player.pos_x -=  eng->map_data->player.dir_y * eng->map_data->player.move_speed;
		if (eng->map_data->map[(int)(eng->map_data->player.pos_y + eng->map_data->player.dir_x* eng->map_data->player.move_speed)][(int)(eng->map_data->player.pos_x)] == '0')
				eng->map_data->player.pos_y +=  eng->map_data->player.dir_x * eng->map_data->player.move_speed;
	}
	calcul(eng, 0);
	draw(eng);
	return (0);
}

void	draw(t_engine *eng)
{
	//ft_bzero(eng->mlx_data->data.data, SCREEN_WIDTH * SCREEN_HEIGHT);
	for (int y = 0; y < SCREEN_HEIGHT; y++)
	{
		for (int x = 0; x < SCREEN_WIDTH; x++)
		{
			eng->mlx_data->data.data[y * SCREEN_WIDTH + x] = eng->mlx_data->buf[y][x];
		}
	}
	mlx_put_image_to_window(eng->mlx_data->mlx, eng->mlx_data->mlx_win, eng->mlx_data->data.img, 0, 0);
}

void    print_line(t_engine *eng, int x, int y1, int y2, int color)
{
    int y;

    y = y1;
	   
	while (y <= y2)
    {
        my_mlx_pixel_put(eng->mlx_data,  x, y, color);
        y++;
    }
}

void	ceiling_or_floor(t_engine *eng, int x, int y, int color, int q)
{
	int i;

	i = 0;
	if (q == 0)
	{
		while (i < y)
		{
			eng->mlx_data->buf[i][x] = color;
			eng->mlx_data->re_buf = 1;
			i++;
		}
	}
	else
	{
		while (y < SCREEN_HEIGHT)
		{
			eng->mlx_data->buf[y][x] = color;
			eng->mlx_data->re_buf = 1;
			y++;
		}
	}
}

void	wall_draw(t_engine *eng, int x, int y, int z)
{
	int	i;
	int	color;

	i = y;
	while (i < z)
	{
		eng->calcul->tex_y = (int)eng->calcul->tex_pos & (texHeight - 1);
		eng->calcul->tex_pos += eng->calcul->step;
		color = eng->mlx_data->texture[eng->calcul->tex_num][texHeight * eng->calcul->tex_y + eng->calcul->tex_x];
		if (eng->calcul->map_x + (1 - eng->calcul->step_x) / 2 > eng->map_data->player.pos_x)
			color = eng->mlx_data->texture[0][texHeight * eng->calcul->tex_y + eng->calcul->tex_x];// NORD
		else
			color = eng->mlx_data->texture[1][texHeight * eng->calcul->tex_y + eng->calcul->tex_x]; // SUD
		if (eng->calcul->side == 1)
		{
			if (eng->calcul->map_y + (1 - eng->calcul->step_y) / 2 > eng->map_data->player.pos_y)
				color = eng->mlx_data->texture[3][texHeight * eng->calcul->tex_y + eng->calcul->tex_x]; //OUEST
			else
				color = eng->mlx_data->texture[2][texHeight * eng->calcul->tex_y + eng->calcul->tex_x];//EST
			color = (color >> 1) & 8355711;
		}
		eng->mlx_data->buf[i][x] = color;
		eng->mlx_data->re_buf = 1;
		i++;
	}
}

void init_var(t_engine *eng, int x)
{
	(void)x;
	eng->calcul->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	eng->calcul->ray_dir_x = eng->map_data->player.dir_x + eng->map_data->player.plane_x * eng->calcul->camera_x;
	eng->calcul->ray_dir_y = eng->map_data->player.dir_y + eng->map_data->player.plane_y * eng->calcul->camera_x;
	eng->calcul->map_x = (int)eng->map_data->player.pos_x;
	eng->calcul->map_y = (int)eng->map_data->player.pos_y;
	eng->calcul->delta_dist_x = fabs(1 / eng->calcul->ray_dir_x);
	eng->calcul->delta_dist_y = fabs(1 / eng->calcul->ray_dir_y);
	eng->calcul->hit = 0;
}


void	calcul_dist_wall(t_engine *eng)
{
	if (eng->calcul->side == 0)
		eng->calcul->perp_wall_dist = (eng->calcul->map_x - eng->map_data->player.pos_x + (1 - eng->calcul->step_x) / 2) / eng->calcul->ray_dir_x;
	else
		eng->calcul->perp_wall_dist = (eng->calcul->map_y - eng->map_data->player.pos_y + (1 - eng->calcul->step_y) / 2) / eng->calcul->ray_dir_y;
	
	if (eng->calcul->side == 0)
		eng->calcul->wall_x = eng->map_data->player.pos_y + eng->calcul->perp_wall_dist * eng->calcul->ray_dir_y;
	else
		eng->calcul->wall_x = eng->map_data->player.pos_x + eng->calcul->perp_wall_dist * eng->calcul->ray_dir_x;
	eng->calcul->wall_x -= floor(eng->calcul->wall_x);
}

void	wall_detect(t_engine *eng)
{
	while (eng->calcul->hit == 0)
	{
		if (eng->calcul->side_dist_x < eng->calcul->side_dist_y)
		{
			eng->calcul->side_dist_x += eng->calcul->delta_dist_x;
			eng->calcul->map_x += eng->calcul->step_x;
			eng->calcul->side = 0;
		}
		else
		{
			eng->calcul->side_dist_y += eng->calcul->delta_dist_y;
			eng->calcul->map_y += eng->calcul->step_y;
			eng->calcul->side = 1;
		}
		if (eng->map_data->map[eng->calcul->map_y][eng->calcul->map_x] > 48)
			eng->calcul->hit = 1;
	}
	calcul_dist_wall(eng);
}


void	init_sideDist(t_engine *eng)
{
	if (eng->calcul->ray_dir_x < 0)
	{
		eng->calcul->step_x = -1;
		eng->calcul->side_dist_x = (eng->map_data->player.pos_x - eng->calcul->map_x) * eng->calcul->delta_dist_x;
	}
	else
	{
		eng->calcul->step_x = 1;
		eng->calcul->side_dist_x = (eng->calcul->map_x + 1.0 - eng->map_data->player.pos_x) * eng->calcul->delta_dist_x;
	}
	if (eng->calcul->ray_dir_y < 0)
	{
		eng->calcul->step_y = -1;
		eng->calcul->side_dist_y = (eng->map_data->player.pos_y - eng->calcul->map_y) * eng->calcul->delta_dist_y;
	}
	else
	{
		eng->calcul->step_y = 1;
		eng->calcul->side_dist_y = (eng->calcul->map_y + 1.0 - eng->map_data->player.pos_y) * eng->calcul->delta_dist_y;
	}
	wall_detect(eng);
}

int calcul(t_engine *eng, int x)
{	
	while (x < SCREEN_WIDTH)
	{
		init_var(eng, x);
		init_sideDist(eng);
		eng->calcul->line_height = (int)(SCREEN_HEIGHT / eng->calcul->perp_wall_dist);
		eng->calcul->draw_start = -(eng->calcul->line_height) / 2 + SCREEN_HEIGHT / 2;
		if(eng->calcul->draw_start < 0)
			eng->calcul->draw_start = 0;
		eng->calcul->draw_end = eng->calcul->line_height / 2 + SCREEN_HEIGHT / 2;
		if(eng->calcul->draw_end >= SCREEN_HEIGHT)
			eng->calcul->draw_end = SCREEN_HEIGHT - 1;
		eng->calcul->tex_num = eng->map_data->map[eng->calcul->map_y][eng->calcul->map_x] - 48;
		eng->calcul->tex_x = (int)(eng->calcul->wall_x * (double)texWidth);
		if (eng->calcul->side == 0 && eng->calcul->ray_dir_x > 0)
			eng->calcul->tex_x = texWidth - eng->calcul->tex_x - 1;
		if (eng->calcul->side == 1 && eng->calcul->ray_dir_y < 0)
			eng->calcul->tex_x = texWidth - eng->calcul->tex_x - 1;
		eng->calcul->step = 1.0 * texHeight / eng->calcul->line_height;
		eng->calcul->tex_pos = (eng->calcul->draw_start - SCREEN_HEIGHT / 2 + eng->calcul->line_height / 2) * eng->calcul->step;
		ceiling_or_floor(eng, x, eng->calcul->draw_start, eng->map_data->ceiling_rgb.color, 0);
		ceiling_or_floor(eng, x, eng->calcul->draw_end, eng->map_data->floor_rgb.color, 1);
		wall_draw(eng, x, eng->calcul->draw_start, eng->calcul->draw_end);
		x++;
	}
	return (0);
}

void	load_image(t_engine *eng, int *texture, char *path, t_data *data)
{
	data->img = mlx_xpm_file_to_image(eng->mlx_data->mlx, path, &data->img_width, &data->img_height);
	data->data = (int *)mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->size_l, &data->endian);
	for (int y = 0; y < data->img_height; y++)
	{
		for (int x = 0; x < data->img_width; x++)
		{
			texture[data->img_width * y + x] = data->data[data->img_width * y + x];
		}
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
		engine->mlx_data->right_pers = 1;
	if (key == 97)
		engine->mlx_data->left_pers = 1;
	if (key == 65361)
		engine->mlx_data->left = 1;
	if (key == 65363)
		engine->mlx_data->right = 1;
	if (key == 65307)
		exit(0); 
	return (0);
}

int	key_release(int key, t_engine *eng)
{
	if (key == 119)
		eng->mlx_data->up = 0;
	if (key == 115)
		eng->mlx_data->down = 0;
	if (key == 100)
		eng->mlx_data->right_pers = 0;
	if (key == 97)
		eng->mlx_data->left_pers = 0;
	if (key == 65361)
		eng->mlx_data->left = 0;
	if (key == 65363)
		eng->mlx_data->right = 0;
	return (0);
}

void	exec_load(t_engine *eng)
{
	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		for (int j = 0; j < SCREEN_WIDTH ; j++)
		{
			eng->mlx_data->buf[i][j] = 0;
		}
	}

	if (!(eng->mlx_data->texture = (int **)malloc(sizeof(int *) * 4))) //aadd to garbage collector
		return ; // quitter qvec une erreur
	for (int i = 0; i < 4; i++)
	{
		if (!(eng->mlx_data->texture[i] = (int *)malloc(sizeof(int) * (texHeight * texWidth)))) //aadd to garbage collector
			return ;// quitter qvec une erreur
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < texHeight * texWidth; j++)
		{
			eng->mlx_data->texture[i][j] = 0;
		}
	}
	load_texture(eng);
}

void	play(t_engine *eng)
{
	eng->mlx_data->mlx = mlx_init();
	init_perso(&eng->map_data->player, (const char **)eng->map_data->map);
	eng->map_data->map[(int)eng->map_data->player.pos_y][(int)eng->map_data->player.pos_x] = '0';
	exec_load(eng);
	eng->mlx_data->re_buf = 0;
	eng->mlx_data->mlx_win = mlx_new_window(eng->mlx_data->mlx, SCREEN_WIDTH , SCREEN_HEIGHT , "cub3d");
    eng->mlx_data->data.img = mlx_new_image(eng->mlx_data->mlx, 1080, 720);
    eng->mlx_data->data.data = (int *)mlx_get_data_addr(eng->mlx_data->data.img, &eng->mlx_data->data.bits_per_pixel, &eng->mlx_data->data.line_length, &eng->mlx_data->data.endian);
	eng->mlx_data->up = 0;
	eng->mlx_data->down = 0;
	eng->mlx_data->right_pers = 0;
	eng->mlx_data->left_pers = 0;
	eng->mlx_data->left = 0;
	eng->mlx_data->right = 0;
	mlx_hook(eng->mlx_data->mlx_win, 2, 1L << 0, &key_press,  eng);
    mlx_hook(eng->mlx_data->mlx_win, 3, 1L << 1, &key_release, eng);
	mlx_loop_hook(eng->mlx_data->mlx, &main_loop, eng);
    mlx_loop(eng->mlx_data->mlx);
}