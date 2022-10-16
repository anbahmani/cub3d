/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 19:34:06 by abahmani          #+#    #+#             */
/*   Updated: 2022/10/16 19:34:25 by abahmani         ###   ########.fr       */
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
		quit_error(FD_ERROR, garb_c);
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

void	get_file_content(t_engine *eng, const char *file_name)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		quit_error(FD_ERROR, eng->garbage_coll);
	i = 0;
	while (i < eng->size_file_content)
	{
		get_next_line(fd, &line);
		ft_lstadd_back(&eng->garbage_coll, ft_lstnew(line));
		eng->file_content[i++] = line;
	}
	eng->file_content[i] = NULL;
	close(fd);
}
