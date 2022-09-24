/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 04:21:48 by abahmani          #+#    #+#             */
/*   Updated: 2022/09/24 04:27:46 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ihm(t_win *mlx_data)
{
	mlx_data->mlx = mlx_init();
	mlx_data->mlx_win = mlx_new_window(mlx_data->mlx,
			SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
}

static void	init_perso_bis(t_perso *perso, const char **map, int i, int j)
{
	perso->posX = j;
	perso->posY = i;
	if (map[i][j] == 'W')
	{
		perso->dirX = -1;
		perso->dirY = 0;
	}
	else if (map[i][j] == 'E')
	{
		perso->dirX = 1;
		perso->dirY = 0;
	}
	else if (map[i][j] == 'N')
	{
		perso->dirX = 0;
		perso->dirY = -1;
	}
	else if (map[i][j] == 'S')
	{
		perso->dirX = 0;
		perso->dirY = 1;
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
	perso->dirX = -1;
	perso->dirY = 0;
	perso->planeX = PERSO_PLANE_X;
	perso->planeY = PERSO_PLANE_Y;
	perso->moveSpeed = PERSO_MOVEMENT_SPEED;
	perso->rotSpeed = PERSO_ROTATION_SPEED;
}
