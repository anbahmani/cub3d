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
#define screenWidth 1080
#define screenHeight 720

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

int main_loop(void)
{
	t_win mlx;
	double posX = 22;
	double posY = 12;
	double dirX = -1;
	double dirY = 0;
	double planeX = 0;
	double planeY = 0.66;
	
	double time = 0;
	double oldTime = 0;

	int x = 0;
	int w;
	
	mlx.mlx = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx, screenWidth, screenHeight, "cub3d");
	while (1)
	{
		while (x < 1080)
		{
			double cameraX = 2 * x / double(w) -1;
			double rayDirX = dirX + planeX * cameraX;
			double rayDirY = dirY + planeY * cameraY;

			int mapX = int(posX);
			int mapY = int(posY);
			double sideDistX;
			double sideDistY;

			double deltaDistX = sqrt(1 + (rayDirY * rayDirY)/ (rayDirX * rayDirX));
			double deltaDistY = sqrt(1 + (rayDirX * rayDirX)/ (rayDirY * rayDirY));
			double perpWallDist;

			int stepX;
			int stepY;

			int hit = 0;
			int side ;

			if (rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (posX - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - posX) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (posY - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - posY) * deltaDistY;
			}
			while (hit == 0)
			{
				//jump to next map square, either in x-direction, or in y-direction
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
				if (worldMap[mapX][mapY] > 0)
					hit = 1;
				if(side == 0) 
					perpWallDist = (sideDistX - deltaDistX);
      			else          
					perpWallDist = (sideDistY - deltaDistY);
					
				int lineHeight = (int)(h / perpWallDist);
				int drawStart = -lineHeight / 2 + h / 2;
				if(drawStart < 0)
					drawStart = 0;
				int drawEnd = lineHeight / 2 + h / 2;
				if(drawEnd >= h)
					drawEnd = h - 1;
				ColorRGB color;
				switch(worldMap[mapX][mapY])
				{
					case 1:  color = RGB_Red;  break; //red
					case 2:  color = RGB_Green;  break; //green
					case 3:  color = RGB_Blue;   break; //blue
					case 4:  color = RGB_White;  break; //white
					default: color = RGB_Yellow; break; //yellow
				}

				//give x and y sides different brightness
				if (side == 1) {color = color / 2;}

				//draw the pixels of the stripe as a vertical line
				verLine(x, drawStart, drawEnd, color);
			} 
			   	oldTime = time;
   				time = getTicks();
   				double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
   				print(1.0 / frameTime); //FPS counter
   				redraw();
   				cls();
			
   				//speed modifiers
   				double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
   				double rotSpeed = frameTime * 3.0;
		}

			
		
	
	
	mlx_loop(mlx.mlx);
	return (0);
}