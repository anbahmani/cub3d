/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 09:20:12 by abahmani          #+#    #+#             */
/*   Updated: 2022/09/13 13:12:24 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_text_file_name(char *line, t_map_data *data, t_texture text)
{
	if (text == NO)
		data->north_text = ft_strtrim(line + 2, " \t");
	else if (text == SO)
		data->south_text = ft_strtrim(line + 2, " \t");
	else if (text == WE)
		data->west_text = ft_strtrim(line + 2, " \t");
	else if (text == EA)
		data->east_text = ft_strtrim(line + 2, " \t");
}

void	set_color(t_rgb *colors, int color, int nb)
{
	if (color == 1)
		colors->red = nb;
	else if (color == 2)
		colors->green = nb;
	else if (color == 3)
		colors->blue = nb;
}

t_rgb	get_color(char *line, t_list *garb_coll)
{
	t_rgb	*colors;
	char	*tmp;
	int		i;
	int		nb;
	int		color;

	tmp = line;
	i = -1;
	nb = 0;
	color = 1;
	line = ft_strtrim(line + 2, " \t");
	free(tmp);
	ft_malloc((void *)colors, sizeof(t_rgb), garb_coll);
	while (color < 4)
	{
		while (line[++i])
		{
			if (ft_isdigit(line[i]))
				nb = (nb + (line[i] + '0')) * 10;
			if (line[i] == ',')
				break ;
		}
		set_color(colors, color, nb);
		color++;
	}
}

void	get_file_data_bis(const char *file_name, t_map_data *data,
		t_list *garb_c, char *line)
{
	if (ft_strncmp((const char *) line, "NO", 2))
		get_text_file_name(line, data, NO);
	else if (ft_strncmp((const char *) line, "SO", 2))
		get_text_file_name(line, data, SO);
	else if (ft_strncmp((const char *) line, "WE", 2))
		get_text_file_name(line, data, WE);
	else if (ft_strncmp((const char *) line, "EA", 2))
		get_text_file_name(line, data, EA);
	else if (ft_strncmp((const char *) line, "C ", 2))
		data->ceiling_rgb = get_color(line, garb_c);
	else if (ft_strncmp((const char *) line, "F ", 2))
		data->floor_rgb = get_color(line, garb_c);
}

void	get_file_data(const char *file_name, t_map_data *data, t_list *garb_c)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file_name, O_RDONLY);
	get_next_line(fd, &line);
	while (*line)
	{
		i = 0;
		while (line[i])
		{
			get_file_data_bis(file_name, data, garb_c, line);
			i++;
		}
		free(line);
		get_next_line(fd, &line);
	}
}
