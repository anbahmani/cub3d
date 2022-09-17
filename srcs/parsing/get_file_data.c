/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 09:20:12 by abahmani          #+#    #+#             */
/*   Updated: 2022/09/17 18:43:16 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_color(t_rgb *colors, char **split)
{
	colors->red = ft_atoi((const char *)split[0]);
	colors->green = ft_atoi((const char *)split[1]);
	colors->blue = ft_atoi((const char *)split[2]);
	clear_str_tab(split);
}

t_rgb	get_color(char *line, t_list *garb_coll)
{
	t_rgb	*colors;
	char	**split;
	int		nb_str;

	split = ft_split(line + 2, ',');
	nb_str = count_str(split);
	if (nb_str > 3 || nb_str < 3)
	{
		clear_str_tab(split);
		clear(garb_coll);
		exit(1);
	}
	trim_split(split);
	if (!composed_with(split[0], "0123456789")
		|| !composed_with(split[1], "0123456789")
		|| !composed_with(split[2], "0123456789"))
	{
		clear_str_tab(split);
		clear(garb_coll);
		exit(1);
	}
	colors = (t_rgb *)ft_malloc(sizeof(t_rgb), garb_coll);
	set_color(colors, split);
	return (*colors);
}

void	get_file_data_bis(t_map_data *data, t_list *garb_c, char *line)
{
	if (!ft_strncmp((const char *) line, "NO ", 3))
		data->north_text = ft_strtrim(line + 2, " \t");
	else if (!ft_strncmp((const char *) line, "SO ", 3))
		data->south_text = ft_strtrim(line + 2, " \t");
	else if (!ft_strncmp((const char *) line, "WE ", 3))
		data->west_text = ft_strtrim(line + 2, " \t");
	else if (!ft_strncmp((const char *) line, "EA ", 3))
		data->east_text = ft_strtrim(line + 2, " \t");
	else if (!ft_strncmp((const char *) line, "C ", 2))
		data->ceiling_rgb = get_color(line, garb_c);
	else if (!ft_strncmp((const char *) line, "F ", 2))
		data->floor_rgb = get_color(line, garb_c);
}

void	get_file_data(const char *file_name, t_map_data *data, t_list *garb_c)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_RDONLY);
	while (get_next_line(fd, &line) != -1)
	{
		ft_lstadd_back(&garb_c, ft_lstnew(line));
		get_file_data_bis(data, garb_c, line);
	}
	close(fd);
}
