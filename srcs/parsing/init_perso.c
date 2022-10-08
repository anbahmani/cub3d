/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_perso.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:09:48 by abahmani          #+#    #+#             */
/*   Updated: 2022/10/08 04:13:05 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_perso_bis(t_engine *eng, int i, int j)
{
	eng->map_data->player.pos_x = j + 0.5;
	eng->map_data->player.pos_y = i + 0.5;
	if (eng->map_data->map[i][j] == 'W')
	{
		eng->map_data->player.dir_x = -1;
		eng->map_data->player.dir_y = 0;
	}
	else if (eng->map_data->map[i][j] == 'E')
	{
		eng->map_data->player.dir_x = 1;
		eng->map_data->player.dir_y = 0;
	}
	else if (eng->map_data->map[i][j] == 'N')
	{
		eng->map_data->player.dir_x = 0;
		eng->map_data->player.dir_y = -1;
	}
	else if (eng->map_data->map[i][j] == 'S')
	{
		eng->map_data->player.dir_x = 0;
		eng->map_data->player.dir_y = 1;
	}
}

void	init_perso(t_engine *eng)
{
	int	i;
	int	j;

	i = 0;
	while (eng->map_data->map[i])
	{
		j = 0;
		while (eng->map_data->map[i][j])
		{
			if (is_orientation_char(eng->map_data->map[i][j]))
			{
				init_perso_bis(eng, i, j);
			}
			j++;
		}
		i++;
	}
	eng->map_data->player.plane_x = (0.66 * eng->map_data->player.dir_y);;
	eng->map_data->player.plane_y = (0.66 * (-1 * eng->map_data->player.dir_x));
	eng->map_data->player.move_speed = PERSO_MOVEMENT_SPEED;
	eng->map_data->player.rot_speed = PERSO_ROTATION_SPEED;
}
