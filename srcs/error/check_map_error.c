/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 06:29:58 by abahmani          #+#    #+#             */
/*   Updated: 2022/09/24 06:33:10 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	last_char(char *str)
{
	int	i;

	i = 0;
	while (str[i + 1])
		i++;
	return (str[i]);
}

static int	check_border_char(char **map)
{
	int	i;
	int	j;

	if (count_str((char const **)map) < 3)
		return (0);
	i = -1;
	while (map[0][++i])
	{
		if (map[0][i] != '1')
			return (0);
	}
	i = 0;
	while (map[++i + 1] != NULL)
	{
		if (map[i][0] != '1' || last_char(map[i]) != '1')
			return (0);
	}
	j = -1;
	while (map[i][++j])
	{
		if (map[i][j] != '1')
			return (0);
	}
	return (1);
}
