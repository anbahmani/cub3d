/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 09:20:12 by abahmani          #+#    #+#             */
/*   Updated: 2022/10/16 19:26:13 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	trim_and_add_gc(char **text, t_engine *eng, char *line)
{
	*text = ft_strtrim(line + 2, " \t");
	ft_lstadd_back(&eng->garbage_coll, ft_lstnew(*text));
}

static int	is_doublon(char *text, t_map_data *data)
{
	if (text)
		data->doublon_text = 1;
	return (1);
}

void	get_file_data_bis(t_engine *eng, char *line)
{
	if (!ft_strncmp((const char *) line, "NO ", 3)
		&& is_doublon(eng->map_data->north_text, eng->map_data))
		trim_and_add_gc(&eng->map_data->north_text, eng, line);
	else if (!ft_strncmp((const char *) line, "SO ", 3)
		&& is_doublon(eng->map_data->south_text, eng->map_data))
		trim_and_add_gc(&eng->map_data->south_text, eng, line);
	else if (!ft_strncmp((const char *) line, "WE ", 3)
		&& is_doublon(eng->map_data->west_text, eng->map_data))
		trim_and_add_gc(&eng->map_data->west_text, eng, line);
	else if (!ft_strncmp((const char *) line, "EA ", 3)
		&& is_doublon(eng->map_data->east_text, eng->map_data))
		trim_and_add_gc(&eng->map_data->east_text, eng, line);
	else if (!ft_strncmp((const char *) line, "C ", 2))
		init_color(eng, line, &eng->map_data->ceiling_rgb);
	else if (!ft_strncmp((const char *) line, "F ", 2))
		init_color(eng, line, &eng->map_data->floor_rgb);
}

void	get_file_data(t_engine *eng)
{
	int	i;

	i = 0;
	while (eng->file_content[i])
	{
		get_file_data_bis(eng, eng->file_content[i]);
		i++;
	}
	if (eng->map_data->doublon_text == 1)
		quit_error(DOUBLON_TEXTURE_ERROR, eng->garbage_coll);
}
