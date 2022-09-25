/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_char_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 15:48:06 by abahmani          #+#    #+#             */
/*   Updated: 2022/09/24 15:49:13 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_number_player(char **map)
{
	int	nb_p;
	int	i;
	int	j;

	nb_p = 0;
	i = 1;
	while (map[i] != NULL)
	{
		j = 1;
		while (map[i][j])
		{
			if (is_orientation_char(map[i][j]))
				nb_p++;
			j++;
		}
		i++;
	}
	return (nb_p == 1);
}

