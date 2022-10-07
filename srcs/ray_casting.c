/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:12:11 by raaga             #+#    #+#             */
/*   Updated: 2022/10/07 14:29:16 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main_loop(t_win *mlx)
{
    if (mlx->up)
	{
		if (!worldMap[(int)(mlx->perso.pos_x + mlx->perso.dir_x * mlx->perso.move_speed)][(int)(mlx->perso.pos_y)])
			mlx->perso.pos_x += mlx->perso.dir_x * mlx->perso.move_speed;
		if (!worldMap[(int)(mlx->perso.pos_x)][(int)(mlx->perso.pos_y + mlx->perso.dir_y * mlx->perso.move_speed)])
			mlx->perso.pos_y += mlx->perso.dir_y * mlx->perso.move_speed;
	}
	if (mlx->down)
	{
		if (!worldMap[(int)(mlx->perso.pos_x - mlx->perso.dir_x * mlx->perso.move_speed)][(int)(mlx->perso.pos_y)])
			mlx->perso.pos_x -= mlx->perso.dir_x * mlx->perso.move_speed;
		if (!worldMap[(int)(mlx->perso.pos_x)][(int)(mlx->perso.pos_y - mlx->perso.dir_y * mlx->perso.move_speed)])
			mlx->perso.pos_y -= mlx->perso.dir_y * mlx->perso.move_speed;
	}
	if (mlx->right)
	{
		double olddir_x = mlx->perso.dir_x;
		mlx->perso.dir_x = mlx->perso.dir_x * cos(-mlx->perso.rot_speed) - mlx->perso.dir_y * sin(-mlx->perso.rot_speed);
		mlx->perso.dir_y = olddir_x * sin(-mlx->perso.rot_speed) + mlx->perso.dir_y * cos(-mlx->perso.rot_speed);
		double oldplane_x = mlx->perso.plane_x;
		mlx->perso.plane_x = mlx->perso.plane_x * cos(-mlx->perso.rot_speed) - mlx->perso.plane_y * sin(-mlx->perso.rot_speed);
		mlx->perso.plane_y = oldplane_x * sin(-mlx->perso.rot_speed) + mlx->perso.plane_y * cos(-mlx->perso.rot_speed);
	}
	if (mlx->left)
	{
		double olddir_x = mlx->perso.dir_x;
		mlx->perso.dir_x = mlx->perso.dir_x * cos(mlx->perso.rot_speed) - mlx->perso.dir_y * sin(mlx->perso.rot_speed);
		mlx->perso.dir_y = olddir_x * sin(mlx->perso.rot_speed) + mlx->perso.dir_y * cos(mlx->perso.rot_speed);
		double oldplane_x = mlx->perso.plane_x;
		mlx->perso.plane_x = mlx->perso.plane_x * cos(mlx->perso.rot_speed) - mlx->perso.plane_y * sin(mlx->perso.rot_speed);
		mlx->perso.plane_y = oldplane_x * sin(mlx->perso.rot_speed) + mlx->perso.plane_y * cos(mlx->perso.rot_speed);
	}
	if (mlx->right_pers)
	{
		printf("asdasdasdadasdasda\n");
		if (!worldMap[(int)(mlx->perso.pos_y)][(int)(mlx->perso.pos_x + mlx->perso.dir_y * mlx->perso.move_speed)])
				mlx->perso.pos_x +=  mlx->perso.dir_y * mlx->perso.move_speed;
		if (!worldMap[(int)(mlx->perso.pos_y - mlx->perso.dir_x* mlx->perso.move_speed)][(int)(mlx->perso.pos_x)])
				mlx->perso.pos_y -=  mlx->perso.dir_x * mlx->perso.move_speed;
	}
	if (mlx->left_pers)
	{
		printf("asdasdasdadasdasda\n");
		if (!worldMap[(int)(mlx->perso.pos_y)][(int)(mlx->perso.pos_x - mlx->perso.dir_y * mlx->perso.move_speed)])
				mlx->perso.pos_x -=  mlx->perso.dir_y * mlx->perso.move_speed;
		if (!worldMap[(int)(mlx->perso.pos_y + mlx->perso.dir_x* mlx->perso.move_speed)][(int)(mlx->perso.pos_x)])
				mlx->perso.pos_y +=  mlx->perso.dir_x * mlx->perso.move_speed;
	}
	calcul(mlx);
	draw(mlx);
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*tmp;
	size_t			i;

	tmp = s;
	i = 0;
	while (i < n)
	{
		*tmp = '\0';
		tmp++;
		i++;
	}
}


void	draw(t_win *mlx)
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			mlx->data.data[y * WIDTH + x] = mlx->buf[y][x];
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->data.img, 0, 0);
	 
}

void    print_line(t_win *data, int x, int y1, int y2, int color)
{
    int y;

    y = y1;
	   
	while (y <= y2)
    {
        my_mlx_pixel_put(data,  x, y, color);
        y++;
    }
}

void	ceiling_or_floor(t_win *mlx, int x, int y, int color)
{
	int i;

	i = 0;
	while (i < y)
	{
		
		i++;
	}
}

int calcul(t_win *mlx)
{	
	int x = 0;
	
		while (x < WIDTH)
		{
			double camera_x = 2 * x / (double)WIDTH - 1;
			double ray_dir_x = mlx->perso.dir_x + mlx->perso.plane_x * camera_x;
			double ray_dir_y = mlx->perso.dir_y + mlx->perso.plane_y * camera_x;

			int map_x = (int)mlx->perso.pos_x;
			int map_y = (int)mlx->perso.pos_y;

			double side_dist_x;
			double side_dist_y;

			double delta_dist_x = fabs(1 / ray_dir_x);
			double delta_dist_y = fabs(1 / ray_dir_y);
			double perp_wall_dist;

			int step_x;
			int step_y;

			int hit = 0;
			int side;

			if (ray_dir_x < 0)
			{
				step_x = -1;
				side_dist_x = (mlx->perso.pos_x - map_x) * delta_dist_x;
			}
			else
			{
				step_x = 1;
				side_dist_x = (map_x + 1.0 - mlx->perso.pos_x) * delta_dist_x;
			}
			if (ray_dir_y < 0)
			{
				step_y = -1;
				side_dist_y = (mlx->perso.pos_y - map_y) * delta_dist_y;
			}
			else
			{
				step_y = 1;
				side_dist_y = (map_y + 1.0 - mlx->perso.pos_y) * delta_dist_y;
			}

			while (hit == 0)
			{
				if (side_dist_x < side_dist_y)
				{
					side_dist_x += delta_dist_x;
					map_x += step_x;
					side = 0;
				}
				else
				{
					side_dist_y += delta_dist_y;
					map_y void	ceiling_or_floor(t_win *mlx, int x, int y, int color)
{
	int i;

	i = 0;
	while (i < y)
	{
		
		i++;
	}
} = -line_height / 2 + HEIGHT / 2;
			if(draw_start < 0)
				draw_start = 0;
			int draw_end = line_height / 2 + HEIGHT / 2;
			if(draw_end >= HEIGHT)
				draw_end = HEIGHT - 1;
			
			int tex_num = worldMap[map_x][map_y];

			double wall_x;
			if (side == 0)
				wall_x = mlx->perso.pos_y + perp_wall_dist * ray_dir_y;
			else
				wall_x = mlx->perso.pos_x + perp_wall_dist * ray_dir_x;
			wall_x -= floor(wall_x);

			int tex_x = (int)(wall_x * (double)texWidth);
			if (side == 0 && ray_dir_x > 0)
				tex_x = texWidth - tex_x - 1;
			if (side == 1 && ray_dir_y < 0)
				tex_x = texWidth - tex_x - 1;

			double step = 1.0 * texHeight / line_height;
			double tex_pos = (draw_start - HEIGHT / 2 + line_height / 2) * step;
			ceiling_or_floor(mlx, x, draw_start, mlx)
			for (int z = 0; z < draw_start; z++)
			{
				mlx->buf[z][x] = mlx->color;
				mlx->re_buf = 1;
			}
			for (int t = draw_end; t < screenHeight; t++)
			{
				mlx->buf[t][x] = 0xFFCC66;
				mlx->re_buf = 1;
			}
			for (int y = draw_start; y < draw_end; y++)
			{
				int tex_y = (int)tex_pos & (texHeight - 1);
				tex_pos += step;
				int color = mlx->texture[tex_num][texHeight * tex_y + tex_x];
				if (map_x + (1 - step_x)/2 > mlx->perso.pos_x)
				{
					color = 0xFFFFFF; // NORD
				}
				else
				{
					color = 0x0000FF; // SUD
				}
				if (side == 1)
				{
					if (map_y + (1 - step_y)/2 > mlx->perso.pos_y)
					{
						color = 0xAAFFFF; //OUEST
					}
					else
					{
						color = 0x0000FF; //EST
					}
					color = (color >> 1) & 8355711;
				}
				mlx->buf[y][x] = color;
				mlx->re_buf = 1;
			}
			x++;
		}
		
	
	return (0);
}

void	load_image(t_win *mlx, int *texture, char *path, t_data *data)
{
	
	data->img = mlx_xpm_file_to_image(mlx->mlx, path, &data->img_width, &data->img_height);
	data->data = (int *)mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->size_l, &data->endian);
	for (int y = 0; y < data->img_height; y++)
	{
		for (int x = 0; x < data->img_width; x++)
		{
			texture[data->img_width * y + x] = data->data[data->img_width * y + x];
		}
	}
	mlx_destroy_image(mlx->mlx, data->img);
}

void	load_texture(t_win *mlx)
{
	t_data img;

	load_image(mlx, mlx->texture[0], "./pics/redbrick.xpm", &img);
	load_image(mlx, mlx->texture[1], "./pics/redbrick.xpm", &img);
	load_image(mlx, mlx->texture[2], "./pics/redbrick.xpm", &img);
	load_image(mlx, mlx->texture[3], "./pics/redbrick.xpm", &img);
	load_image(mlx, mlx->texture[4], "./pics/redbrick.xpm", &img);
	load_image(mlx, mlx->texture[5], "./pics/redbrick.xpm", &img);
	load_image(mlx, mlx->texture[6], "./pics/redbrick.xpm", &img);
	load_image(mlx, mlx->texture[7],"./pics/redbrick.xpm", &img);
}



int	key_press(int key, t_win *mlx)
{	
	printf("pourpour %d\n", key);
	if (key == 119)
	{
		mlx->up = 1;
	}
	if (key == 115)
	{
		mlx->down = 1;
	}
	if (key == 100)
	{
		
		mlx->right_pers = 1;
	}
	if (key == 97)
	{
		mlx->left_pers = 1;

	}
	if (key == 65361)
	{
		//left_pers;
		mlx->left = 1;
		
	}
	if (key == 65363)
	{
		mlx->right = 1;
	}

	
	if (key == 65307)
		exit(0); 
	
	//mlx_clear_window(mlx->mlx, mlx->mlx_win);
	main_loop(mlx);
	return (0);
}

int	key_release(int key, t_win *mlx)
{
	if (key == 119)
	{
		mlx->up = 0;
	}
	if (key == 115)
	{
		mlx->down = 0;
	}
	if (key == 100)
	{
		mlx->right_pers = 0;
	}
	if (key == 97)
	{
		mlx->left_pers = 0;
	}
	if (key == 65361)
		mlx->left = 0;	
	if (key == 65363)
		mlx->right = 0;
	
	if (key == 53)
		exit(0); 
	//mlx_clear_window(mlx->mlx, mlx->mlx_win);
	main_loop(mlx);
	return (0);
}