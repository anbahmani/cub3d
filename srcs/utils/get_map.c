/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 22:44:28 by abahmani          #+#    #+#             */
/*   Updated: 2022/09/13 18:12:46 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_file_line(char const *file_name)
{
	int		fd;
	int		cmp;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (-1);
	cmp = 0;
	while (get_next_line(fd, &line))
	{
		free(line);
		cmp++;
	}
	free(line);
	close(fd);
	return (cmp + 1);
}

char	**get_map(char *line, int start, const char *file_name)
{
	char	**map;
	int		fd;

	fd = open(file_name, O_RDONLY);
	
}

void	find_map(const char *file_name, t_map_data *data, t_list *garb_c)
{
	int		fd;
	int		i;
	char	*line;
	char	*tmp;

	fd = open(file_name, O_RDONLY);
	get_next_line(fd, &line);
	i = 0;
	while (line)
	{
		tmp = ft_strtrim(line, " \t");
		if (composed_with(tmp, " \t10NWES"))
			break ;
		free(tmp);
		free(line);
		get_next_line(fd, &line);
		i++;
	}
	if (line)
		free(tmp);
	close(fd);
	data->map = get_map(line, i, file_name);
}
