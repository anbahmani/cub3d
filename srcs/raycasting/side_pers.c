/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   side_pers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 07:20:08 by abahmani          #+#    #+#             */
/*   Updated: 2022/10/08 07:25:17 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	right_pers(t_engine *eng)
{
	if (eng->mlx_data->right_pers)
	{
		if (eng->map_data->map[(int)(eng->map_data->player.pos_y)]
			[(int)(eng->map_data->player.pos_x + eng->map_data->player.dir_y
			* eng->map_data->player.move_speed)] == '0')
			eng->map_data->player.pos_x += eng->map_data->player.dir_y
				* eng->map_data->player.move_speed;
		if (eng->map_data->map[(int)(eng->map_data->player.pos_y
				- eng->map_data->player.dir_x
				* eng->map_data->player.move_speed)]
			[(int)(eng->map_data->player.pos_x)] == '0')
				eng->map_data->player.pos_y -= eng->map_data->player.dir_x
				* eng->map_data->player.move_speed;
	}
}

void	left_pers(t_engine *eng)
{
	if (eng->mlx_data->left_pers)
	{
		if (eng->map_data->map[(int)(eng->map_data->player.pos_y)]
			[(int)(eng->map_data->player.pos_x - eng->map_data->player.dir_y
			* eng->map_data->player.move_speed)] == '0')
				eng->map_data->player.pos_x -= eng->map_data->player.dir_y
				* eng->map_data->player.move_speed;
		if (eng->map_data->map[(int)(eng->map_data->player.pos_y
				+ eng->map_data->player.dir_x
				* eng->map_data->player.move_speed)]
			[(int)(eng->map_data->player.pos_x)] == '0')
				eng->map_data->player.pos_y += eng->map_data->player.dir_x
				* eng->map_data->player.move_speed;
	}
}
