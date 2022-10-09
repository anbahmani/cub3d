/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 19:01:58 by abahmani          #+#    #+#             */
/*   Updated: 2022/10/09 19:08:10 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calcul_dist_wall(t_engine *eng)
{
	if (eng->calcul->side == 0)
	{
		eng->calcul->perp_wall_dist = (eng->calcul->map_x
				- eng->map_data->player.pos_x + (1 - eng->calcul->step_x) / 2)
			/ eng->calcul->ray_dir_x;
	}
	else
	{
		eng->calcul->perp_wall_dist = (eng->calcul->map_y
				- eng->map_data->player.pos_y + (1 - eng->calcul->step_y) / 2)
			/ eng->calcul->ray_dir_y;
	}
	if (eng->calcul->side == 0)
	{
		eng->calcul->wall_x = eng->map_data->player.pos_y
			+ eng->calcul->perp_wall_dist * eng->calcul->ray_dir_y;
	}
	else
	{
		eng->calcul->wall_x = eng->map_data->player.pos_x
			+ eng->calcul->perp_wall_dist * eng->calcul->ray_dir_x;
	}
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

void	calcul_wall_color_east_west(t_engine *eng, int *color)
{
	if (eng->calcul->side == 1)
	{
		if (eng->calcul->map_y + (1 - eng->calcul->step_y)
			/ 2 > eng->map_data->player.pos_y)
		{
			*color = eng->mlx_data->texture[3]
			[texHeight * eng->calcul->tex_y + eng->calcul->tex_x]; //OUEST
		}
		else
		{
			*color = eng->mlx_data->texture[2]
			[texHeight * eng->calcul->tex_y + eng->calcul->tex_x];//EST
		}
		*color = (*color >> 1) & 8355711;
	}
}

void	calcul_wall_color_south_north(t_engine *eng, int *color)
{
	if (eng->calcul->map_x + (1 - eng->calcul->step_x)
		/ 2 > eng->map_data->player.pos_x)
	{
		*color = eng->mlx_data->texture[0]
		[texHeight * eng->calcul->tex_y + eng->calcul->tex_x];// NORD
	}
	else
	{
		*color = eng->mlx_data->texture[1]
		[texHeight * eng->calcul->tex_y + eng->calcul->tex_x]; // SUD
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
		color = eng->mlx_data->texture[eng->calcul->tex_num]
		[texHeight * eng->calcul->tex_y + eng->calcul->tex_x];
		calcul_wall_color_south_north(eng, &color);
		calcul_wall_color_east_west(eng, &color);
		eng->mlx_data->buf[i][x] = color;
		eng->mlx_data->re_buf = 1;
		i++;
	}
}
