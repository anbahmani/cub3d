/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 04:43:02 by abahmani          #+#    #+#             */
/*   Updated: 2022/10/16 09:52:34 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_data_error(t_engine *eng)
{
	if (eng->map_data->ceiling_rgb.init == 0
		|| eng->map_data->floor_rgb.init == 0)
		quit_error(COLOR_ERROR, eng->garbage_coll);
}
