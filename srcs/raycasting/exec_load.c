/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:00:01 by abahmani          #+#    #+#             */
/*   Updated: 2022/10/15 18:00:29 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	malloc_texture(t_engine *eng)
{
	int	i;
	int	j;

	eng->mlx_data->texture = (int **)ft_malloc(sizeof(int *)
			* 4, eng->garbage_coll);
	if (!(eng->mlx_data->texture))
		quit_error(MALLOC_ERROR, eng->garbage_coll);
	i = -1;
	while (++i < 4)
	{
		eng->mlx_data->texture[i] = (int *)ft_malloc(sizeof(int) * (TEX_HEIGHT
					* TEX_WIDTH), eng->garbage_coll);
		if (!eng->mlx_data->texture[i])
			quit_error(MALLOC_ERROR, eng->garbage_coll);
	}
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < TEX_HEIGHT * TEX_WIDTH)
			eng->mlx_data->texture[i][j] = 0;
	}
}

void	exec_load(t_engine *eng)
{
	int	i;
	int	j;

	i = -1;
	while (++i < SCREEN_HEIGHT)
	{
		j = -1;
		while (++j < SCREEN_WIDTH)
			eng->mlx_data->buf[i][j] = 0;
	}
	malloc_texture(eng);
	load_texture(eng);
}
