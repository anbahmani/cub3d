/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:12:11 by raaga             #+#    #+#             */
/*   Updated: 2022/10/03 20:55:12 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

int	main_loop(t_win *mlx)
{
    if (mlx->up)
	{
		if (!worldMap[(int)(mlx->perso.posX + mlx->perso.dirX * mlx->perso.moveSpeed)][(int)(mlx->perso.posY)])
			mlx->perso.posX += mlx->perso.dirX * mlx->perso.moveSpeed;
		if (!worldMap[(int)(mlx->perso.posX)][(int)(mlx->perso.posY + mlx->perso.dirY * mlx->perso.moveSpeed)])
			mlx->perso.posY += mlx->perso.dirY * mlx->perso.moveSpeed;
	}
	if (mlx->down)
	{
		if (!worldMap[(int)(mlx->perso.posX - mlx->perso.dirX * mlx->perso.moveSpeed)][(int)(mlx->perso.posY)])
			mlx->perso.posX -= mlx->perso.dirX * mlx->perso.moveSpeed;
		if (!worldMap[(int)(mlx->perso.posX)][(int)(mlx->perso.posY - mlx->perso.dirY * mlx->perso.moveSpeed)])
			mlx->perso.posY -= mlx->perso.dirY * mlx->perso.moveSpeed;
	}
	if (mlx->right)
	{
		double oldDirX = mlx->perso.dirX;
		mlx->perso.dirX = mlx->perso.dirX * cos(-mlx->perso.rotSpeed) - mlx->perso.dirY * sin(-mlx->perso.rotSpeed);
		mlx->perso.dirY = oldDirX * sin(-mlx->perso.rotSpeed) + mlx->perso.dirY * cos(-mlx->perso.rotSpeed);
		double oldPlaneX = mlx->perso.planeX;
		mlx->perso.planeX = mlx->perso.planeX * cos(-mlx->perso.rotSpeed) - mlx->perso.planeY * sin(-mlx->perso.rotSpeed);
		mlx->perso.planeY = oldPlaneX * sin(-mlx->perso.rotSpeed) + mlx->perso.planeY * cos(-mlx->perso.rotSpeed);
	}
	if (mlx->left)
	{
		double oldDirX = mlx->perso.dirX;
		mlx->perso.dirX = mlx->perso.dirX * cos(mlx->perso.rotSpeed) - mlx->perso.dirY * sin(mlx->perso.rotSpeed);
		mlx->perso.dirY = oldDirX * sin(mlx->perso.rotSpeed) + mlx->perso.dirY * cos(mlx->perso.rotSpeed);
		double oldPlaneX = mlx->perso.planeX;
		mlx->perso.planeX = mlx->perso.planeX * cos(mlx->perso.rotSpeed) - mlx->perso.planeY * sin(mlx->perso.rotSpeed);
		mlx->perso.planeY = oldPlaneX * sin(mlx->perso.rotSpeed) + mlx->perso.planeY * cos(mlx->perso.rotSpeed);
	}
	if (mlx->right_pers)
	{
		if (!worldMap[(int)(mlx->perso.posX + mlx->perso.dirY * mlx->perso.moveSpeed)][(int)(mlx->perso.posY)])
				mlx->perso.posX +=  mlx->perso.dirY * mlx->perso.moveSpeed;
		if (!worldMap[(int)(mlx->perso.posX)][(int)(mlx->perso.posY - mlx->perso.dirX* mlx->perso.moveSpeed)])
				mlx->perso.posY -=  mlx->perso.dirX * mlx->perso.moveSpeed;
	}
	if (mlx->left_pers)
	{
		if (!worldMap[(int)(mlx->perso.posX - mlx->perso.dirY * mlx->perso.moveSpeed)][(int)(mlx->perso.posY)])
				mlx->perso.posX -=  mlx->perso.dirY * mlx->perso.moveSpeed;
		if (!worldMap[(int)(mlx->perso.posX)][(int)(mlx->perso.posY + mlx->perso.dirX* mlx->perso.moveSpeed)])
				mlx->perso.posY +=  mlx->perso.dirX * mlx->perso.moveSpeed;
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

int calcul(t_win *mlx)
{	
	int x = 0;
	
		while (x < WIDTH)
		{
			double cameraX = 2 * x / (double)WIDTH - 1;
			double rayDirX = mlx->perso.dirX + mlx->perso.planeX * cameraX;
			double rayDirY = mlx->perso.dirY + mlx->perso.planeY * cameraX;

			int mapX = (int)mlx->perso.posX;
			int mapY = (int)mlx->perso.posY;

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
				sideDistX = (mlx->perso.posX - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - mlx->perso.posX) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (mlx->perso.posY - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - mlx->perso.posY) * deltaDistY;
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
				if (worldMap[mapX][mapY] > 0) 
					hit = 1;
			}
			if (side == 0)
				perpWallDist = (mapX - mlx->perso.posX + (1 - stepX) / 2) / rayDirX;
			else
				perpWallDist = (mapY - mlx->perso.posY + (1 - stepY) / 2) / rayDirY;

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
				wallX = mlx->perso.posY + perpWallDist * rayDirY;
			else
				wallX = mlx->perso.posX + perpWallDist * rayDirX;
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
				mlx->buf[z][x] = mlx->color;
				mlx->re_buf = 1;
			}
			for (int t = drawEnd; t < screenHeight; t++)
			{
				mlx->buf[t][x] = 0xFFCC66;
				mlx->re_buf = 1;
			}
			for (int y = drawStart; y < drawEnd; y++)
			{
				int texY = (int)texPos & (texHeight - 1);
				texPos += step;
				int color = mlx->texture[texNum][texHeight * texY + texX];
				if (side == 1)
					color = (color >> 1) & 8355711;
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