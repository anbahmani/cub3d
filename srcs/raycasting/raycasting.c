/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 04:06:55 by abahmani          #+#    #+#             */
/*   Updated: 2022/10/06 21:06:18 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main_loop(t_engine *eng)
{
	double	old_dir_x;
	double	old_plane_x;
	
	if (eng->mlx_data->up)
	{
		if (eng->map_data->map[(int)(eng->map_data->player.posY)][(int)(eng->map_data->player.posX + eng->map_data->player.dirX * eng->map_data->player.moveSpeed)] == '0')
			eng->map_data->player.posX += eng->map_data->player.dirX * eng->map_data->player.moveSpeed;
		if (eng->map_data->map[(int)(eng->map_data->player.posY + eng->map_data->player.dirY * eng->map_data->player.moveSpeed)][(int)(eng->map_data->player.posX)] == '0')
			eng->map_data->player.posY += eng->map_data->player.dirY * eng->map_data->player.moveSpeed;
	}
	if (eng->mlx_data->down)
	{
		if (eng->map_data->map[(int)(eng->map_data->player.posY)][(int)(eng->map_data->player.posX - eng->map_data->player.dirX * eng->map_data->player.moveSpeed)] == '0')
			eng->map_data->player.posX -= eng->map_data->player.dirX * eng->map_data->player.moveSpeed;
		if (eng->map_data->map[(int)(eng->map_data->player.posY - eng->map_data->player.dirY * eng->map_data->player.moveSpeed)][(int)(eng->map_data->player.posX)] == '0')
			eng->map_data->player.posY -= eng->map_data->player.dirY * eng->map_data->player.moveSpeed;
	}
	if (eng->mlx_data->right)
	{
		old_dir_x = eng->map_data->player.dirX;
		eng->map_data->player.dirX = eng->map_data->player.dirX * cos(-eng->map_data->player.rotSpeed) - eng->map_data->player.dirY * sin(-eng->map_data->player.rotSpeed);
		eng->map_data->player.dirY = old_dir_x * sin(-eng->map_data->player.rotSpeed) + eng->map_data->player.dirY * cos(-eng->map_data->player.rotSpeed);
		old_plane_x = eng->map_data->player.planeX;
		eng->map_data->player.planeX = eng->map_data->player.planeX * cos(-eng->map_data->player.rotSpeed) - eng->map_data->player.planeY * sin(-eng->map_data->player.rotSpeed);
		eng->map_data->player.planeY = old_plane_x * sin(-eng->map_data->player.rotSpeed) + eng->map_data->player.planeY * cos(-eng->map_data->player.rotSpeed);
	}
	if (eng->mlx_data->left)
	{
		old_dir_x = eng->map_data->player.dirX;
		eng->map_data->player.dirX = eng->map_data->player.dirX * cos(eng->map_data->player.rotSpeed) - eng->map_data->player.dirY * sin(eng->map_data->player.rotSpeed);
		eng->map_data->player.dirY = old_dir_x * sin(eng->map_data->player.rotSpeed) + eng->map_data->player.dirY * cos(eng->map_data->player.rotSpeed);
		old_plane_x = eng->map_data->player.planeX;
		eng->map_data->player.planeX = eng->map_data->player.planeX * cos(eng->map_data->player.rotSpeed) - eng->map_data->player.planeY * sin(eng->map_data->player.rotSpeed);
		eng->map_data->player.planeY = old_plane_x * sin(eng->map_data->player.rotSpeed) + eng->map_data->player.planeY * cos(eng->map_data->player.rotSpeed);
	}
	if (eng->mlx_data->right_pers)
	{
		if (eng->map_data->map[(int)(eng->map_data->player.posY)][(int)(eng->map_data->player.posX + eng->map_data->player.dirY * eng->map_data->player.moveSpeed)] == '0')
				eng->map_data->player.posX +=  eng->map_data->player.dirY * eng->map_data->player.moveSpeed;
		if (eng->map_data->map[(int)(eng->map_data->player.posY - eng->map_data->player.dirX* eng->map_data->player.moveSpeed)][(int)(eng->map_data->player.posX)] == '0')
				eng->map_data->player.posY -=  eng->map_data->player.dirX * eng->map_data->player.moveSpeed;
	}
	if (eng->mlx_data->left_pers)
	{
		if (eng->map_data->map[(int)(eng->map_data->player.posY)][(int)(eng->map_data->player.posX - eng->map_data->player.dirY * eng->map_data->player.moveSpeed)] == '0')
				eng->map_data->player.posX -=  eng->map_data->player.dirY * eng->map_data->player.moveSpeed;
		if (eng->map_data->map[(int)(eng->map_data->player.posY + eng->map_data->player.dirX* eng->map_data->player.moveSpeed)][(int)(eng->map_data->player.posX)] == '0')
				eng->map_data->player.posY +=  eng->map_data->player.dirX * eng->map_data->player.moveSpeed;
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
	int i;

	i = y;
	while (i < z)
	{
		int texY = (int)eng->calcul->texPos & (texHeight - 1);
		eng->calcul->texPos += eng->calcul->step;
		int color = eng->mlx_data->texture[eng->calcul->texNum][texHeight * texY + eng->calcul->texX];

		if (eng->calcul->mapX + (1 - eng->calcul->stepX)/2 > eng->map_data->player.posX)
			color = eng->mlx_data->texture[0][texHeight * texY + eng->calcul->texX];// NORD
		else
			color = eng->mlx_data->texture[1][texHeight * texY + eng->calcul->texX]; // SUD
		if (eng->calcul->side == 1)
		{
			if (eng->calcul->mapY + (1 - eng->calcul->stepY)/2 > eng->map_data->player.posY)
				color = eng->mlx_data->texture[3][texHeight * texY + eng->calcul->texX]; //OUEST
			else
				color = eng->mlx_data->texture[2][texHeight * texY + eng->calcul->texX];//EST
			color = (color >> 1) & 8355711;
		}
		eng->mlx_data->buf[i][x] = color;
		eng->mlx_data->re_buf = 1;
		i++;
	}
}

void init_var(t_engine *eng, int x)
{
	eng->calcul->cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
	eng->calcul->rayDirX = eng->map_data->player.dirX + eng->map_data->player.planeX * eng->calcul->cameraX;
	eng->calcul->rayDirY = eng->map_data->player.dirY + eng->map_data->player.planeY * eng->calcul->cameraX;
	eng->calcul->mapX = (int)eng->map_data->player.posX;
	eng->calcul->mapY = (int)eng->map_data->player.posY;
	eng->calcul->deltaDistX = fabs(1 / eng->calcul->rayDirX);
	eng->calcul->deltaDistY = fabs(1 / eng->calcul->rayDirY);
	eng->calcul->hit = 0;
}


void	calcul_dist_wall(t_engine *eng)
{
	if (eng->calcul->side == 0)
		eng->calcul->perpWallDist = (eng->calcul->mapX - eng->map_data->player.posX + (1 - eng->calcul->stepX) / 2) / eng->calcul->rayDirX;
	else
		eng->calcul->perpWallDist = (eng->calcul->mapY - eng->map_data->player.posY + (1 - eng->calcul->stepY) / 2) / eng->calcul->rayDirY;
	
	if (eng->calcul->side == 0)
		eng->calcul->wallX = eng->map_data->player.posY + eng->calcul->perpWallDist * eng->calcul->rayDirY;
	else
		eng->calcul->wallX = eng->map_data->player.posX + eng->calcul->perpWallDist * eng->calcul->rayDirX;
	eng->calcul->wallX -= floor(eng->calcul->wallX);
}

void	wall_detect(t_engine *eng)
{
	while (eng->calcul->hit == 0)
	{
		if (eng->calcul->sideDistX < eng->calcul->sideDistY)
		{
			eng->calcul->sideDistX += eng->calcul->deltaDistX;
			eng->calcul->mapX += eng->calcul->stepX;
			eng->calcul->side = 0;
		}
		else
		{
			eng->calcul->sideDistY += eng->calcul->deltaDistY;
			eng->calcul->mapY += eng->calcul->stepY;
			eng->calcul->side = 1;
		}
		if (eng->map_data->map[eng->calcul->mapY][eng->calcul->mapX] > 48)
			eng->calcul->hit = 1;
	}
	calcul_dist_wall(eng);
}


void	init_sideDist(t_engine *eng)
{
	if (eng->calcul->rayDirX < 0)
	{
		eng->calcul->stepX = -1;
		eng->calcul->sideDistX = (eng->map_data->player.posX - eng->calcul->mapX) * eng->calcul->deltaDistX;
	}
	else
	{
		eng->calcul->stepX = 1;
		eng->calcul->sideDistX = (eng->calcul->mapX + 1.0 - eng->map_data->player.posX) * eng->calcul->deltaDistX;
	}
	if (eng->calcul->rayDirY < 0)
	{
		eng->calcul->stepY = -1;
		eng->calcul->sideDistY = (eng->map_data->player.posY - eng->calcul->mapY) * eng->calcul->deltaDistY;
	}
	else
	{
		eng->calcul->stepY = 1;
		eng->calcul->sideDistY = (eng->calcul->mapY + 1.0 - eng->map_data->player.posY) * eng->calcul->deltaDistY;
	}
	wall_detect(eng);
}

int calcul(t_engine *eng, int x)
{	
	while (x < SCREEN_WIDTH)
	{
		init_var(eng, x);
		init_sideDist(eng);
		eng->calcul->lineHeight = (int)(SCREEN_HEIGHT / eng->calcul->perpWallDist);
		eng->calcul->drawStart = -(eng->calcul->lineHeight) / 2 + SCREEN_HEIGHT / 2;
		if(eng->calcul->drawStart < 0)
			eng->calcul->drawStart = 0;
		eng->calcul->drawEnd = eng->calcul->lineHeight / 2 + SCREEN_HEIGHT / 2;
		if(eng->calcul->drawEnd >= SCREEN_HEIGHT)
			eng->calcul->drawEnd = SCREEN_HEIGHT - 1;
		eng->calcul->texX = (int)(eng->calcul->wallX * (double)texWidth);
		if (eng->calcul->side == 0 && eng->calcul->rayDirX > 0)
			eng->calcul->texX = texWidth - eng->calcul->texX - 1;
		if (eng->calcul->side == 1 && eng->calcul->rayDirY < 0)
			eng->calcul->texX = texWidth - eng->calcul->texX - 1;
		eng->calcul->step = 1.0 * texHeight / eng->calcul->lineHeight;
		eng->calcul->texPos = (eng->calcul->drawStart - SCREEN_HEIGHT / 2 + eng->calcul->lineHeight / 2) * eng->calcul->step;
		ceiling_or_floor(eng, x, eng->calcul->drawStart, eng->map_data->ceiling_rgb.color, 0);
		ceiling_or_floor(eng, x, eng->calcul->drawEnd, eng->map_data->floor_rgb.color, 1);
		wall_draw(eng, x, eng->calcul->drawStart, eng->calcul->drawEnd);
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
	main_loop(engine);
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
	eng->map_data->map[(int)eng->map_data->player.posY][(int)eng->map_data->player.posX] = '0';
	exec_load(eng);
	eng->mlx_data->re_buf = 0;
	eng->mlx_data->mlx_win = mlx_new_window(eng->mlx_data->mlx, SCREEN_WIDTH , SCREEN_HEIGHT , "cub3d");
    eng->mlx_data->data.img = mlx_new_image(eng->mlx_data->mlx, 1080, 720);
    eng->mlx_data->data.data = (int *)mlx_get_data_addr(eng->mlx_data->data.img, &eng->mlx_data->data.bits_per_pixel, &eng->mlx_data->data.line_length, &eng->mlx_data->data.endian);
	mlx_hook(eng->mlx_data->mlx_win, 2, 1L << 0, &key_press,  eng);
    mlx_hook(eng->mlx_data->mlx_win, 3, 1L << 1, &key_release, eng);
	mlx_loop_hook(eng->mlx_data->mlx, &main_loop, eng);
    mlx_loop(eng->mlx_data->mlx);
}