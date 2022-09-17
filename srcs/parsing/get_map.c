/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 22:44:28 by abahmani          #+#    #+#             */
/*   Updated: 2022/09/17 18:48:10 by abahmani         ###   ########.fr       */
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
	while (get_next_line(fd, &line) != -1)
	{
		ft_lstadd_back(&garb_c, ft_lstnew(line));
		cmp++;
	}
	close(fd);
	return (cmp);
}

int	is_map_line(char *line)
{
	int	i;
	int	no_map_comp;

	i = 0;
	no_map_comp = 0;
	while (line[i])
	{
		if (!is_in_set(line[i], " \t10NWES"))
			return (0);
		if (is_in_set(line[i], "10NWES"))
			no_map_comp++;
		i++;
	}
	return (no_map_comp);
}

static void	iter_gnl(int start, int fd, t_list *garb_c)
{
	int		i;
	char	*line;

	i = 0;
	while (i < start)
	{
		get_next_line(fd, &line);
		ft_lstadd_back(&garb_c, ft_lstnew(line));
		i++;
	}
}

char	**get_map(int start, const char *file_name, t_list *garb_c)
{
	char	**map;
	int		fd;
	int		i;
	char	*line;

	map = ft_malloc(sizeof(char *) * count_file_line(file_name,
				garb_c) - start + 1, garb_c);
	fd = open(file_name, O_RDONLY);
	iter_gnl(start, fd, garb_c);
	i = 0;
	while (get_next_line(fd, &line) != -1)
	{
		map[i] = line;
		i++;
	}
	map[i] = NULL;
	close(fd);
	return (copy_tab(map, garb_c));
}

void	find_map(const char *file_name, t_map_data *data, t_list *garb_c)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		quit_error(FD_ERROR, garb_c);
	i = 0;
	while (get_next_line(fd, &line) != -1)
	{
		ft_lstadd_back(&garb_c, ft_lstnew(line));
		if (is_map_line(line))
			break ;
		i++;
	}
	while (get_next_line(fd, &line))
		ft_lstadd_back(&garb_c, ft_lstnew(line));
	close(fd);
	data->map = get_map(i, file_name, garb_c);
}
