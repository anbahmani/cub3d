/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 06:29:58 by abahmani          #+#    #+#             */
/*   Updated: 2022/10/12 15:58:38 by abahmani         ###   ########.fr       */
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


static int	check_char_around(const char **map, int i, int j)
{
	if (i == 0 || i == count_str((char **)map) - 1 || j == 0
		|| j == (int)ft_strlen(map[0]) - 1)
		return (0);
	if (map[i - 1][j] == '-' || map[i + 1][j] == '-' || map[i][j - 1] == '-'
		|| map[i][j + 1] == '-')
		return (0);
	return (1);
}

int	check_map(const char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || is_orientation_char(map[i][j]))
			{
				if (!check_char_around(map, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (check_number_player((char **)map));
}
