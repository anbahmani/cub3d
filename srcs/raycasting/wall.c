/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 19:01:58 by abahmani          #+#    #+#             */
/*   Updated: 2022/10/19 16:57:28 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calcul_dist_wall(t_engine *eng)
{
	if (eng->cal->side == 0)
	{
		eng->cal->perp_wall_dist = (eng->cal->map_x
				- eng->map_data->player.pos_x + (1 - eng->cal->step_x) / 2)
			/ eng->cal->ray_dir_x;
	}
	else
	{
		eng->cal->perp_wall_dist = (eng->cal->map_y
				- eng->map_data->player.pos_y + (1 - eng->cal->step_y) / 2)
			/ eng->cal->ray_dir_y;
	}
	if (eng->cal->side == 0)
	{
		eng->cal->wall_x = eng->map_data->player.pos_y
			+ eng->cal->perp_wall_dist * eng->cal->ray_dir_y;
	}
	else
	{
		eng->cal->wall_x = eng->map_data->player.pos_x
			+ eng->cal->perp_wall_dist * eng->cal->ray_dir_x;
	}
	eng->cal->wall_x -= floor(eng->cal->wall_x);
}

void	wall_detect(t_engine *eng)
{
	while (eng->cal->hit == 0)
	{
		if (eng->cal->side_dist_x < eng->cal->side_dist_y)
		{
			eng->cal->side_dist_x += eng->cal->delta_dist_x;
			eng->cal->map_x += eng->cal->step_x;
			eng->cal->side = 0;
		}
		else
		{
			eng->cal->side_dist_y += eng->cal->delta_dist_y;
			eng->cal->map_y += eng->cal->step_y;
			eng->cal->side = 1;
		}
		if (eng->map_data->map[eng->cal->map_y][eng->cal->map_x] > 48)
			eng->cal->hit = 1;
	}
	calcul_dist_wall(eng);
}

void	calcul_wall_color_east_west(t_engine *eng, int *color)
{
	if (eng->cal->side == 1)
	{
		if (eng->cal->map_y + (1 - eng->cal->step_y)
			/ 2 > eng->map_data->player.pos_y)
		{
			*color = eng->mlx_data->texture[0]
			[TEX_HEIGHT * eng->cal->tex_y + eng->cal->tex_x];
		}
		else
		{
			*color = eng->mlx_data->texture[1]
			[TEX_HEIGHT * eng->cal->tex_y + eng->cal->tex_x];
		}	
	}
}

void	calcul_wall_color_south_north(t_engine *eng, int *color)
{
	if (eng->cal->map_x + (1 - eng->cal->step_x)
		/ 2 > eng->map_data->player.pos_x)
	{
		*color = eng->mlx_data->texture[3]
		[TEX_HEIGHT * eng->cal->tex_y + eng->cal->tex_x];
	}
	else
	{
		*color = eng->mlx_data->texture[2]
		[TEX_HEIGHT * eng->cal->tex_y + eng->cal->tex_x];
	}
	*color = (*color >> 1) & 8355711;
}

void	wall_draw(t_engine *eng, int x, int y, int z)
{
	int	i;
	int	color;

	i = y;
	while (i < z)
	{
		eng->cal->tex_y = (int)eng->cal->tex_pos & (TEX_HEIGHT - 1);
		eng->cal->tex_pos += eng->cal->step;
		color = eng->mlx_data->texture[eng->cal->tex_num]
		[TEX_HEIGHT * eng->cal->tex_y + eng->cal->tex_x];
		calcul_wall_color_south_north(eng, &color);
		calcul_wall_color_east_west(eng, &color);
		eng->mlx_data->buf[i][x] = color;
		eng->mlx_data->re_buf = 1;
		i++;
	}
}
