/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 16:12:31 by abahmani          #+#    #+#             */
/*   Updated: 2022/10/15 18:02:54 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calcul_text(t_engine *eng)
{
	eng->cal->tex_num = eng->map_data->map[eng->cal->map_y][eng->cal->map_x]
		- 48;
	eng->cal->tex_x = (int)(eng->cal->wall_x * (double)TEX_WIDTH);
	if (eng->cal->side == 0 && eng->cal->ray_dir_x > 0)
		eng->cal->tex_x = TEX_WIDTH - eng->cal->tex_x - 1;
	if (eng->cal->side == 1 && eng->cal->ray_dir_y < 0)
		eng->cal->tex_y = TEX_WIDTH - eng->cal->tex_x - 1;
}

int	calcul(t_engine *eng, int x)
{	
	while (x < SCREEN_WIDTH)
	{
		init_var(eng, x);
		init_side_dist(eng);
		eng->cal->line_height = (int)(SCREEN_HEIGHT / eng->cal->perp_wall_dist);
		eng->cal->draw_start = -(eng->cal->line_height) / 2 + SCREEN_HEIGHT / 2;
		if (eng->cal->draw_start < 0)
			eng->cal->draw_start = 0;
		eng->cal->draw_end = eng->cal->line_height / 2 + SCREEN_HEIGHT / 2;
		if (eng->cal->draw_end >= SCREEN_HEIGHT)
			eng->cal->draw_end = SCREEN_HEIGHT - 1;
		calcul_text(eng);
		eng->cal->step = 1.0 * TEX_HEIGHT / eng->cal->line_height;
		eng->cal->tex_pos = (eng->cal->draw_start - SCREEN_HEIGHT / 2
				+ eng->cal->line_height / 2) * eng->cal->step;
		ceiling_or_floor(eng, x, 0);
		ceiling_or_floor(eng, x, 1);
		wall_draw(eng, x, eng->cal->draw_start, eng->cal->draw_end);
		x++;
	}
	return (0);
}
