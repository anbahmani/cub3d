/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 22:44:28 by abahmani          #+#    #+#             */
/*   Updated: 2022/09/15 00:33:33 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_file_line(char const *file_name, t_list *garb_c)
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
		ft_lstadd_back(&garb_c, ft_lstnew(line));
		cmp++;
	}
	close(fd);
	return (cmp + 1);
}

char	**get_map(int start, const char *file_name, t_list *garb_c)
{
	char	**map;
	int		fd;
	int		i;
	char	*line;

	map = ft_malloc(sizeof(char *) * count_file_line(file_name, garb_c),
			garb_c);
	fd = open(file_name, O_RDONLY);
	i = 0;
	while (i < start)
	{
		get_next_line(fd, &line);
		ft_lstadd_back(&garb_c, ft_lstnew(line));
		i++;
	}
	i = 0;
	while (get_next_line(fd, &line) != -1)
	{
		ft_lstadd_back(&garb_c, ft_lstnew(line));
		map[i] = line;
	}
	close(fd);
	return (map);
}

void	find_map(const char *file_name, t_map_data *data, t_list *garb_c)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		quit_error(FD_ERROR, garb_c);
	get_next_line(fd, &line);
	ft_lstadd_back(&garb_c, ft_lstnew(line));
	i = 0;
	while (line)
	{
		if (composed_with(line, " \t10NWES"))
			break ;
		get_next_line(fd, &line);
		ft_lstadd_back(&garb_c, ft_lstnew(line));
		i++;
	}
	close(fd);
	data->map = get_map(i, file_name, garb_c);
}
