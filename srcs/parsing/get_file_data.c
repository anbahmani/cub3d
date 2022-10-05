/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 09:20:12 by abahmani          #+#    #+#             */
/*   Updated: 2022/10/05 17:59:31 by abahmani         ###   ########.fr       */
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
		quit_error(COLOR_ERROR, garb_coll);
	}
	colors = (t_rgb *)ft_malloc(sizeof(t_rgb), garb_coll);
	printf("lstsize color -> %d\n", ft_lstsize(garb_coll));
	set_color(colors, split);
	return (*colors);
}

static void	trim_and_add_gc(char **text, t_list *garb_c, char *line)
{
	*text = ft_strtrim(line + 2, " \t");
	ft_lstadd_back(&garb_c, ft_lstnew(*text));
}

void	get_file_data_bis(t_map_data *data, t_list *garb_c, char *line)
{
	if (!ft_strncmp((const char *) line, "NO ", 3))
		trim_and_add_gc(&data->north_text, garb_c, line);
	else if (!ft_strncmp((const char *) line, "SO ", 3))
		trim_and_add_gc(&data->south_text, garb_c, line);
	else if (!ft_strncmp((const char *) line, "WE ", 3))
		trim_and_add_gc(&data->west_text, garb_c, line);
	else if (!ft_strncmp((const char *) line, "EA ", 3))
		trim_and_add_gc(&data->east_text, garb_c, line);
	else if (!ft_strncmp((const char *) line, "C ", 2))
	{
		data->ceiling_rgb = get_color(line, garb_c);
		data->ceiling_rgb.color = pow((double)data->ceiling_rgb.red, 3.00);
		data->ceiling_rgb.color += pow((double)data->ceiling_rgb.green, 2.00);
		data->ceiling_rgb.color += data->ceiling_rgb.blue;
	}
	else if (!ft_strncmp((const char *) line, "F ", 2))
	{
		data->floor_rgb = get_color(line, garb_c);
		data->floor_rgb.color = pow((double)data->floor_rgb.red, 3.00);
		data->floor_rgb.color += pow((double)data->floor_rgb.green, 2.00);
		data->floor_rgb.color += data->floor_rgb.blue;
	}
		
}

void	get_file_data(const char *file_name, t_map_data *data, t_list *garb_c)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_RDONLY);
	while (get_next_line(fd, &line) != -1)
	{
		ft_lstadd_back(&garb_c, ft_lstnew(line));
		printf("lstsize gnl get data -> %d\n", ft_lstsize(garb_c));
		get_file_data_bis(data, garb_c, line);
	}
	if (line)
		ft_lstadd_back(&garb_c, ft_lstnew(line));
	close(fd);
}
