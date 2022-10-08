/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_element.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 05:58:50 by abahmani          #+#    #+#             */
/*   Updated: 2022/10/08 02:48:32 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_orientation_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

static unsigned int	get_max_width(const char **map)
{
	unsigned int	size;
	int	i;
	unsigned int	str_size;

	i = 0;
	size = 0;
	while (map[i])
	{
		str_size = ft_strlen(map[i]);
		if (str_size > size)
			size = str_size;
		i++;
	}
	return (size);
}

static void	copy_and_fill(const char *str, char *line, unsigned int width)
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			line[i] = str[i];
		else
			line[i] = '-';
		i++;
	}
	while (i < width)
	{
		line[i] = '-';
		i++;
	}
	line[i] = '\0';
}

void	fill_map(t_map_data *data, t_list *garb_c)
{
	unsigned int	width;
	char	*line;
	int		i;
	
	width = get_max_width((const char **)data->map);
	i = 0;
	while (data->map[i])
	{
		line = ft_malloc(sizeof(char) * (width + 1), garb_c);
		copy_and_fill((const char *)data->map[i], line, width);
		data->map[i] = line;
		i++;
	}
}
