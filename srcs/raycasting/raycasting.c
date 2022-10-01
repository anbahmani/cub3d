/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 04:06:55 by abahmani          #+#    #+#             */
/*   Updated: 2022/10/01 08:35:57 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int worldMap[mapWidth][mapHeight]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int	main_loop(t_engine *eng)
{
    if (eng->mlx_data->up)
	{
		if (!worldMap[(int)(eng->map_data->player.posX + eng->map_data->player.dirX * eng->map_data->player.moveSpeed)][(int)(eng->map_data->player.posY)])
			eng->map_data->player.posX += eng->map_data->player.dirX * eng->map_data->player.moveSpeed;
		if (!worldMap[(int)(eng->map_data->player.posX)][(int)(eng->map_data->player.posY + eng->map_data->player.dirY * eng->map_data->player.moveSpeed)])
			eng->map_data->player.posY += eng->map_data->player.dirY * eng->map_data->player.moveSpeed;
	}
	if (eng->mlx_data->down)
	{
		if (!worldMap[(int)(eng->map_data->player.posX - eng->map_data->player.dirX * eng->map_data->player.moveSpeed)][(int)(eng->map_data->player.posY)])
			eng->map_data->player.posX -= eng->map_data->player.dirX * eng->map_data->player.moveSpeed;
		if (!worldMap[(int)(eng->map_data->player.posX)][(int)(eng->map_data->player.posY - eng->map_data->player.dirY * eng->map_data->player.moveSpeed)])
			eng->map_data->player.posY -= eng->map_data->player.dirY * eng->map_data->player.moveSpeed;
	}
	if (eng->mlx_data->right)
	{
		double oldDirX = eng->map_data->player.dirX;
		eng->map_data->player.dirX = eng->map_data->player.dirX * cos(-eng->map_data->player.rotSpeed) - eng->map_data->player.dirY * sin(-eng->map_data->player.rotSpeed);
		eng->map_data->player.dirY = oldDirX * sin(-eng->map_data->player.rotSpeed) + eng->map_data->player.dirY * cos(-eng->map_data->player.rotSpeed);
		double oldPlaneX = eng->map_data->player.planeX;
		eng->map_data->player.planeX = eng->map_data->player.planeX * cos(-eng->map_data->player.rotSpeed) - eng->map_data->player.planeY * sin(-eng->map_data->player.rotSpeed);
		eng->map_data->player.planeY = oldPlaneX * sin(-eng->map_data->player.rotSpeed) + eng->map_data->player.planeY * cos(-eng->map_data->player.rotSpeed);
	}
	if (eng->mlx_data->left)
	{
		double oldDirX = eng->map_data->player.dirX;
		eng->map_data->player.dirX = eng->map_data->player.dirX * cos(eng->map_data->player.rotSpeed) - eng->map_data->player.dirY * sin(eng->map_data->player.rotSpeed);
		eng->map_data->player.dirY = oldDirX * sin(eng->map_data->player.rotSpeed) + eng->map_data->player.dirY * cos(eng->map_data->player.rotSpeed);
		double oldPlaneX = eng->map_data->player.planeX;
		eng->map_data->player.planeX = eng->map_data->player.planeX * cos(eng->map_data->player.rotSpeed) - eng->map_data->player.planeY * sin(eng->map_data->player.rotSpeed);
		eng->map_data->player.planeY = oldPlaneX * sin(eng->map_data->player.rotSpeed) + eng->map_data->player.planeY * cos(eng->map_data->player.rotSpeed);
	}
	/* si dirY ou dirX est negative ou pas le 1 change */
	if (eng->mlx_data->right_pers)
	{
		if (eng->map_data->player.dirX >= 0 && eng->map_data->player.dirY >= 0)
		{
			if (!worldMap[(int)(eng->map_data->player.posX + ((1 - eng->map_data->player.dirX) * eng->map_data->player.moveSpeed))][(int)(eng->map_data->player.posY)])
				eng->map_data->player.posX +=  (1 - eng->map_data->player.dirX) * eng->map_data->player.moveSpeed;
			if (!worldMap[(int)(eng->map_data->player.posX)][(int)(eng->map_data->player.posY - (1 - eng->map_data->player.dirY)* eng->map_data->player.moveSpeed)])
				eng->map_data->player.posY -=  (1 - eng->map_data->player.dirY) * eng->map_data->player.moveSpeed;
		}
		else if (eng->map_data->player.dirX < 0 && eng->map_data->player.dirY >= 0)
		{
			if (!worldMap[(int)(eng->map_data->player.posX - ((1 + eng->map_data->player.dirX) * eng->map_data->player.moveSpeed))][(int)(eng->map_data->player.posY)])
				eng->map_data->player.posX += (1 + eng->map_data->player.dirX) * eng->map_data->player.moveSpeed;
			if (!worldMap[(int)(eng->map_data->player.posX)][(int)(eng->map_data->player.posY + (1 - eng->map_data->player.dirY)* eng->map_data->player.moveSpeed)])
				eng->map_data->player.posY += (1 - eng->map_data->player.dirY)* eng->map_data->player.moveSpeed;
		}
	
		else if (eng->map_data->player.dirY < 0 && eng->map_data->player.dirX < 0)
		{
			if (!worldMap[(int)(eng->map_data->player.posX)][(int)(eng->map_data->player.posY + ((1 - eng->map_data->player.dirY)* eng->map_data->player.moveSpeed))])
				eng->map_data->player.posY += (1 + eng->map_data->player.dirY)* eng->map_data->player.moveSpeed;
			if (!worldMap[(int)(eng->map_data->player.posX - ((1 + eng->map_data->player.dirX) * eng->map_data->player.moveSpeed))][(int)(eng->map_data->player.posY)])
				eng->map_data->player.posX -= (1 + eng->map_data->player.dirX) * eng->map_data->player.moveSpeed;
		}
		else if (eng->map_data->player.dirY < 0 && eng->map_data->player.dirX >= 0)
		{
			if (!worldMap[(int)(eng->map_data->player.posX)][(int)(eng->map_data->player.posY - ((1 + eng->map_data->player.dirY)* eng->map_data->player.moveSpeed))])
				eng->map_data->player.posY -= (1 + eng->map_data->player.dirY)* eng->map_data->player.moveSpeed;
			if (!worldMap[(int)(eng->map_data->player.posX - ((1 - eng->map_data->player.dirX) * eng->map_data->player.moveSpeed))][(int)(eng->map_data->player.posY)])
				eng->map_data->player.posX -= (1 - eng->map_data->player.dirX) * eng->map_data->player.moveSpeed;
		}
	}
	if (eng->mlx_data->left_pers)
	{
		if (eng->map_data->player.dirX >= 0 && eng->map_data->player.dirY >= 0)
		{
			if (!worldMap[(int)(eng->map_data->player.posX - ((1 - eng->map_data->player.dirX) * eng->map_data->player.moveSpeed))][(int)(eng->map_data->player.posY)])
				eng->map_data->player.posX -=  (1 - eng->map_data->player.dirX) * eng->map_data->player.moveSpeed;
			if (!worldMap[(int)(eng->map_data->player.posX)][(int)(eng->map_data->player.posY + (1 - eng->map_data->player.dirY)* eng->map_data->player.moveSpeed)])
				eng->map_data->player.posY +=  (1 - eng->map_data->player.dirY) * eng->map_data->player.moveSpeed;
		}
		else if (eng->map_data->player.dirX < 0 && eng->map_data->player.dirY >= 0)
		{
			if (!worldMap[(int)(eng->map_data->player.posX - ((1 + eng->map_data->player.dirX) * eng->map_data->player.moveSpeed))][(int)(eng->map_data->player.posY)])
				eng->map_data->player.posX -= (1 + eng->map_data->player.dirX) * eng->map_data->player.moveSpeed;
			if (!worldMap[(int)(eng->map_data->player.posX)][(int)(eng->map_data->player.posY - (1 - eng->map_data->player.dirY)* eng->map_data->player.moveSpeed)])
				eng->map_data->player.posY -= (1 - eng->map_data->player.dirY)* eng->map_data->player.moveSpeed;
		}
	
		else if (eng->map_data->player.dirY < 0 && eng->map_data->player.dirX < 0)
		{
			if (!worldMap[(int)(eng->map_data->player.posX)][(int)(eng->map_data->player.posY - ((1 - eng->map_data->player.dirY)* eng->map_data->player.moveSpeed))])
				eng->map_data->player.posY -= (1 + eng->map_data->player.dirY)* eng->map_data->player.moveSpeed;
			if (!worldMap[(int)(eng->map_data->player.posX + ((1 + eng->map_data->player.dirX) * eng->map_data->player.moveSpeed))][(int)(eng->map_data->player.posY)])
				eng->map_data->player.posX += (1 + eng->map_data->player.dirX) * eng->map_data->player.moveSpeed;
		}
		else if (eng->map_data->player.dirY < 0 && eng->map_data->player.dirX >= 0)
		{
			if (!worldMap[(int)(eng->map_data->player.posX)][(int)(eng->map_data->player.posY + ((1 + eng->map_data->player.dirY)* eng->map_data->player.moveSpeed))])
				eng->map_data->player.posY += (1 + eng->map_data->player.dirY)* eng->map_data->player.moveSpeed;
			if (!worldMap[(int)(eng->map_data->player.posX + ((1 - eng->map_data->player.dirX) * eng->map_data->player.moveSpeed))][(int)(eng->map_data->player.posY)])
				eng->map_data->player.posX += (1 - eng->map_data->player.dirX) * eng->map_data->player.moveSpeed;
		}
	}
	calcul(eng->mlx_data);
	draw(eng->mlx_data);
	return (0);
}

void	draw(t_engine *eng)
{
	ft_bzero(eng->mlx_data->data.data, SCREEN_WIDTH * SCREEN_HEIGHT);
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			eng->mlx_data->data.data[y * WIDTH + x] = eng->mlx_data->buf[y][x];
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

int calcul(t_engine *eng)
{	
	int x = 0;
	
		while (x < WIDTH)
		{
			double cameraX = 2 * x / (double)WIDTH - 1;
			double rayDirX = eng->map_data->player.dirX + eng->map_data->player.planeX * cameraX;
			double rayDirY = eng->map_data->player.dirY + eng->map_data->player.planeY * cameraX;

			int mapX = (int)eng->map_data->player.posX;
			int mapY = (int)eng->map_data->player.posY;

			double sideDistX;
			double sideDistY;

			double deltaDistX = fabs(1 / rayDirX);
			double deltaDistY = fabs(1 / rayDirY);
			double perpWallDist;

			int stepX;
			int stepY;

			int hit = 0;
			int side;

			if (rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (eng->map_data->player.posX - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - eng->map_data->player.posX) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (eng->map_data->player.posY - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - eng->map_data->player.posY) * deltaDistY;
			}

			while (hit == 0)
			{
				if (sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
				}
				if (worldMap[mapX][mapY] > 0) hit = 1;
			}
			if (side == 0)
				perpWallDist = (mapX - eng->map_data->player.posX + (1 - stepX) / 2) / rayDirX;
			else
				perpWallDist = (mapY - eng->map_data->player.posY + (1 - stepY) / 2) / rayDirY;

			int lineHeight = (int)(HEIGHT / perpWallDist);

			int drawStart = -lineHeight / 2 + HEIGHT / 2;
			if(drawStart < 0)
				drawStart = 0;
			int drawEnd = lineHeight / 2 + HEIGHT / 2;
			if(drawEnd >= HEIGHT)
				drawEnd = HEIGHT - 1;
			
			int texNum = worldMap[mapX][mapY];

			double wallX;
			if (side == 0)
				wallX = eng->map_data->player.posY + perpWallDist * rayDirY;
			else
				wallX = eng->map_data->player.posX + perpWallDist * rayDirX;
			wallX -= floor(wallX);

			int texX = (int)(wallX * (double)texWidth);
			if (side == 0 && rayDirX > 0)
				texX = texWidth - texX - 1;
			if (side == 1 && rayDirY < 0)
				texX = texWidth - texX - 1;

			double step = 1.0 * texHeight / lineHeight;
			double texPos = (drawStart - HEIGHT / 2 + lineHeight / 2) * step;
			for (int z = 0; z < drawStart; z++)
			{
				eng->mlx_data->buf[z][x] = eng->mlx_data->color;
				eng->mlx_data->re_buf = 1;
			}
			for (int t = drawEnd; t < SCREEN_HEIGHT; t++)
			{
				eng->mlx_data->buf[t][x] = 0xFFCC66;
				eng->mlx_data->re_buf = 1;
			}
			for (int y = drawStart; y < drawEnd; y++)
			{
				int texY = (int)texPos & (texHeight - 1);
				texPos += step;
				int color = eng->mlx_data->texture[texNum][texHeight * texY + texX];
				if (side == 1)
					color = (color >> 1) & 8355711;
				eng->mlx_data->buf[y][x] = color;
				eng->mlx_data->re_buf = 1;
			}
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



int	key_press(int key, t_engine *engine)
{	
	fprintf(stderr, "lslsl %d\n", key);
	if (key == 119)
	{
		engine->mlx_data->up = 1;
	}
	if (key == 115)
	{
		engine->mlx_data->down = 1;
	}
	if (key == 100)
	{
		engine->mlx_data->right = 1;

	}
	if (key == 97)
	{
		engine->mlx_data->left = 1;
	}
	if (key == 65361)
	{
		//left_pers;
		engine->mlx_data->left_pers = 1;
	}
	if (key == 65363)
	{
		engine->mlx_data->right_pers = 1;
	}

	
	if (key == 65307)
		exit(0); 
	mlx_clear_window(engine->mlx_data->mlx, engine->mlx_data->mlx_win);
	main_loop(engine->mlx_data);
	return (0);
}

int	key_release(int key, t_engine *eng)
{
	if (key == 119)
	{
		eng->mlx_data->up = 0;
	}
	if (key == 115)
	{
		eng->mlx_data->down = 0;
	}
	if (key == 100)
	{
		eng->mlx_data->right = 0;

	}
	if (key == 97)
	{
		eng->mlx_data->left = 0;
	}
	if (key == 65361)
		eng->mlx_data->left_pers = 0;
	if (key == 65363)
		eng->mlx_data->right_pers = 0;
	
/*	if (key == 53)
		exit(0); 
	mlx_clear_window(mlx->mlx, mlx->mlx_win);
	main_loop(mlx);*/
	return (0);
}
/*
int	key_release(int key, t_win *mlx)
{
	if (key == 119)
	{
		if (!worldMap[(int)(mlx->perso.posX + mlx->perso.dirX * mlx->perso.moveSpeed)][(int)(mlx->perso.posY)])
			mlx->perso.posX += mlx->perso.dirX * mlx->perso.moveSpeed;
		if (!worldMap[(int)(mlx->perso.posX)][(int)(mlx->perso.posY + mlx->perso.dirY * mlx->perso.moveSpeed)])
			mlx->perso.posY += mlx->perso.dirY * mlx->perso.moveSpeed;
	}
	if (key == 115)
	{
		if (!worldMap[(int)(mlx->perso.posX - mlx->perso.dirX * mlx->perso.moveSpeed)][(int)(mlx->perso.posY)])
			mlx->perso.posX -= mlx->perso.dirX * mlx->perso.moveSpeed;
		if (!worldMap[(int)(mlx->perso.posX)][(int)(mlx->perso.posY - mlx->perso.dirY * mlx->perso.moveSpeed)])
			mlx->perso.posY -= mlx->perso.dirY * mlx->perso.moveSpeed;
	}
	if (key == 100)
	{
		double oldDirX = mlx->perso.dirX;
		mlx->perso.dirX = mlx->perso.dirX * cos(-mlx->perso.rotSpeed) - mlx->perso.dirY * sin(-mlx->perso.rotSpeed);
		mlx->perso.dirY = oldDirX * sin(-mlx->perso.rotSpeed) + mlx->perso.dirY * cos(-mlx->perso.rotSpeed);
		double oldPlaneX = mlx->perso.planeX;
		mlx->perso.planeX = mlx->perso.planeX * cos(-mlx->perso.rotSpeed) - mlx->perso.planeY * sin(-mlx->perso.rotSpeed);
		mlx->perso.planeY = oldPlaneX * sin(-mlx->perso.rotSpeed) + mlx->perso.planeY * cos(-mlx->perso.rotSpeed);
	}
	if (key == 97)
	{
		double oldDirX = mlx->perso.dirX;
		mlx->perso.dirX = mlx->perso.dirX * cos(mlx->perso.rotSpeed) - mlx->perso.dirY * sin(mlx->perso.rotSpeed);
		mlx->perso.dirY = oldDirX * sin(mlx->perso.rotSpeed) + mlx->perso.dirY * cos(mlx->perso.rotSpeed);
		double oldPlaneX = mlx->perso.planeX;
		mlx->perso.planeX = mlx->perso.planeX * cos(mlx->perso.rotSpeed) - mlx->perso.planeY * sin(mlx->perso.rotSpeed);
		mlx->perso.planeY = oldPlaneX * sin(mlx->perso.rotSpeed) + mlx->perso.planeY * cos(mlx->perso.rotSpeed);
	}
	
	if (key == 53)
		exit(0); 
	mlx_clear_window(mlx->mlx, mlx->mlx_win);
	main_loop(mlx);
	return (0);
}*/