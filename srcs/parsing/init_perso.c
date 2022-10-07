/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_perso.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:09:48 by abahmani          #+#    #+#             */
/*   Updated: 2022/10/07 14:27:57 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_perso_bis(t_perso *perso, const char **map, int i, int j)
{
	perso->pos_x = j + 0.5;
	perso->pos_y = i + 0.5;
	if (map[i][j] == 'W')
	{
		perso->dir_x = -1;
		perso->dir_y = 0;
	}
	else if (map[i][j] == 'E')
	{
		perso->dir_x = 1;
		perso->dir_y = 0;
	}
	else if (map[i][j] == 'N')
	{
		perso->dir_x = 0;
		perso->dir_y = -1;
	}
	else if (map[i][j] == 'S')
	{
		perso->dir_x = 0;
		perso->dir_y = 1;
	}
}

void	init_perso(t_perso *perso, const char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_orientation_char(map[i][j]))
			{
				init_perso_bis(perso, map, i, j);
			}
			j++;
		}
		i++;
	}
	perso->dir_x = -1;
	perso->dir_y = 0;
	perso->plane_x = (0.66 * perso->dir_y);;
	perso->plane_y = (0.66 * (-1 * perso->dir_x));
	perso->move_speed = PERSO_MOVEMENT_SPEED;
	perso->rot_speed = PERSO_ROTATION_SPEED;
}
