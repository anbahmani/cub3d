/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:12:11 by raaga             #+#    #+#             */
/*   Updated: 2022/09/21 20:20:01 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#define mapWidth 24
#define mapHeight 24
#define width 1920
#define height 1080

int worldMap[mapWidth][mapHeight]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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
	
		while (x < width)
		{
			double cameraX = 2 * x / (double)width - 1;
			double rayDirX = mlx->perso.dirX + mlx->perso.planeX * cameraX;
			double rayDirY = mlx->perso.dirY + mlx->perso.planeY * cameraX;

			int mapX = (int)mlx->perso.posX;
			int mapY = (int)mlx->perso.posY;

			//length of ray from current position to next x or y-side
			double sideDistX;
			double sideDistY;

			 //length of ray from one x or y-side to next x or y-side
			double deltaDistX = fabs(1 / rayDirX);
			double deltaDistY = fabs(1 / rayDirY);
			double perpWallDist;

			//what direction to step in x or y-direction (either +1 or -1)
			int stepX;
			int stepY;

			int hit = 0; //was there a wall hit?
			int side; //was a NS or a EW wall hit?

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
				//jump to next map square, OR in x-direction, OR in y-direction
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
				//Check if ray has hit a wall
				if (worldMap[mapX][mapY] > 0) hit = 1;
			}
			if (side == 0)
				perpWallDist = (mapX - mlx->perso.posX + (1 - stepX) / 2) / rayDirX;
			else
				perpWallDist = (mapY - mlx->perso.posY + (1 - stepY) / 2) / rayDirY;

			//Calculate height of line to draw on screen
			int lineHeight = (int)(height / perpWallDist);

			//calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + height / 2;
			if(drawStart < 0)
				drawStart = 0;
			int drawEnd = lineHeight / 2 + height / 2;
			if(drawEnd >= height)
				drawEnd = height - 1;

			int	color;
			if (worldMap[mapY][mapX] == 1)
				color = 0xFF0000;
			else if (worldMap[mapY][mapX] == 2)
				color = 0x00FF00;
			else if (worldMap[mapY][mapX] == 3)
				color = 0x0000FF;
			else if (worldMap[mapY][mapX] == 4)
				color = 0xFFFFFF;
			else
				color = 0xFFFF00;

			if (side == 1)
				color = color / 2;

			print_line(mlx, x, drawStart, drawEnd, color);

			x++;
		}
	
	return (0);
}

int	key_press(int key, t_win *mlx)
{
	fprintf(stderr, "lslslsl %d\n", key);
	if (key == 119)
	{
		if (!worldMap[(int)(mlx->perso.posX + mlx->perso.dirX * mlx->perso.moveSpeed)][(int)(mlx->perso.posY)])
			mlx->perso.posX += mlx->perso.dirX * mlx->perso.moveSpeed;
		if (!worldMap[(int)(mlx->perso.posX)][(int)(mlx->perso.posY + mlx->perso.dirY * mlx->perso.moveSpeed)])
			mlx->perso.posY += mlx->perso.dirY * mlx->perso.moveSpeed;
	}
	//move backwards if no wall behind you
	if (key == 115)
	{
		if (!worldMap[(int)(mlx->perso.posX - mlx->perso.dirX * mlx->perso.moveSpeed)][(int)(mlx->perso.posY)])
			mlx->perso.posX -= mlx->perso.dirX * mlx->perso.moveSpeed;
		if (!worldMap[(int)(mlx->perso.posX)][(int)(mlx->perso.posY - mlx->perso.dirY * mlx->perso.moveSpeed)])
			mlx->perso.posY -= mlx->perso.dirY * mlx->perso.moveSpeed;
	}
	//rotate to the right
	if (key == 100)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = mlx->perso.dirX;
		mlx->perso.dirX = mlx->perso.dirX * cos(-mlx->perso.rotSpeed) - mlx->perso.dirY * sin(-mlx->perso.rotSpeed);
		mlx->perso.dirY = oldDirX * sin(-mlx->perso.rotSpeed) + mlx->perso.dirY * cos(-mlx->perso.rotSpeed);
		double oldPlaneX = mlx->perso.planeX;
		mlx->perso.planeX = mlx->perso.planeX * cos(-mlx->perso.rotSpeed) - mlx->perso.planeY * sin(-mlx->perso.rotSpeed);
		mlx->perso.planeY = oldPlaneX * sin(-mlx->perso.rotSpeed) + mlx->perso.planeY * cos(-mlx->perso.rotSpeed);
	}
	//rotate to the left
	if (key == 97)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = mlx->perso.dirX;
		mlx->perso.dirX = mlx->perso.dirX * cos(mlx->perso.rotSpeed) - mlx->perso.dirY * sin(mlx->perso.rotSpeed);
		mlx->perso.dirY = oldDirX * sin(mlx->perso.rotSpeed) + mlx->perso.dirY * cos(mlx->perso.rotSpeed);
		double oldPlaneX = mlx->perso.planeX;
		mlx->perso.planeX = mlx->perso.planeX * cos(mlx->perso.rotSpeed) - mlx->perso.planeY * sin(mlx->perso.rotSpeed);
		mlx->perso.planeY = oldPlaneX * sin(mlx->perso.rotSpeed) + mlx->perso.planeY * cos(mlx->perso.rotSpeed);
	}
	
	if (key == 53)
		exit(0);
	return (0);
}