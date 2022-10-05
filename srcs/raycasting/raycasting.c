/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 04:06:55 by abahmani          #+#    #+#             */
/*   Updated: 2022/10/05 20:57:22 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
int eng->map_data->map[mapWidth][mapHeight]=
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
*/
int	main_loop(t_engine *eng)
{
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
	calcul(eng);
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

int calcul(t_engine *eng)
{	
	int x = 0;
	
		while (x < SCREEN_WIDTH)
		{
			double cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
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
				if (eng->map_data->map[mapY][mapX] > 48)
					hit = 1;
			}
			
			if (side == 0)
				perpWallDist = (mapX - eng->map_data->player.posX + (1 - stepX) / 2) / rayDirX;
			else
				perpWallDist = (mapY - eng->map_data->player.posY + (1 - stepY) / 2) / rayDirY;

			int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

			int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
			if(drawStart < 0)
				drawStart = 0;
			int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
			if(drawEnd >= SCREEN_HEIGHT)
				drawEnd = SCREEN_HEIGHT - 1;
			
			int texNum = eng->map_data->map[mapY][mapX] - 48;
			
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
			double texPos = (drawStart - SCREEN_HEIGHT / 2 + lineHeight / 2) * step;
			for (int z = 0; z < drawStart; z++)
			{
				eng->mlx_data->buf[z][x] = eng->map_data->ceiling_rgb.color;
				eng->mlx_data->re_buf = 1;
			}
			for (int t = drawEnd; t < SCREEN_HEIGHT; t++)
			{
				eng->mlx_data->buf[t][x] = eng->map_data->floor_rgb.color;
				eng->mlx_data->re_buf = 1;
			}
			for (int y = drawStart; y < drawEnd; y++)
			{
				int texY = (int)texPos & (texHeight - 1);
				
				texPos += step;
				int color = eng->mlx_data->texture[texNum][texHeight * texY + texX];
				
				if (mapX + (1 - stepX)/2 > eng->map_data->player.posX)
				{
					color = eng->mlx_data->texture[0][texHeight * texY + texX];// NORD
				}
				else
				{
					color = eng->mlx_data->texture[1][texHeight * texY + texX]; // SUD
				}
				
				if (side == 1)
				{
					if (mapY + (1 - stepY)/2 > eng->map_data->player.posY)
						color = eng->mlx_data->texture[3][texHeight * texY + texX]; //OUEST
					else
						color = eng->mlx_data->texture[2][texHeight * texY + texX];//EST
					color = (color >> 1) & 8355711;
				}
				
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
	{
		engine->mlx_data->up = 1;
	}
	if (key == 115)
	{
		engine->mlx_data->down = 1;
	}
	if (key == 100)
	{
		engine->mlx_data->right_pers = 1;
	}
	if (key == 97)
	{
		engine->mlx_data->left_pers = 1;
		
	}
	if (key == 65361)
	{
		engine->mlx_data->left = 1;
	}
	if (key == 65363)
	{
		engine->mlx_data->right = 1;
	}
	if (key == 65307)
		exit(0); 
	main_loop(engine);
	
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
		eng->mlx_data->right_pers = 0;

	}
	if (key == 97)
	{
		eng->mlx_data->left_pers = 0;
	}
	if (key == 65361)
		eng->mlx_data->left = 0;

	if (key == 65363)
		eng->mlx_data->right = 0;
		
	
/*	if (key == 53)
		exit(0); 
	mlx_clear_window(mlx->mlx, mlx->mlx_win);
	main_loop(mlx);*/
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