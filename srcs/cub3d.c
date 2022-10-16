/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 14:11:20 by abahmani          #+#    #+#             */
/*   Updated: 2022/10/16 19:34:21 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_engine *eng, const char *file_name)
{
	eng->map_data->north_text = NULL;
	eng->map_data->south_text = NULL;
	eng->map_data->west_text = NULL;
	eng->map_data->east_text = NULL;
	eng->map_data->ceiling_rgb.init = 0;
	eng->map_data->floor_rgb.init = 0;
	eng->map_data->doublon_text = 0;
	get_file_content(eng, file_name);
}

void	check_screen_error(void)
{
	if (SCREEN_WIDTH < 720 || SCREEN_WIDTH > 1080 || SCREEN_HEIGHT < 480
		|| SCREEN_HEIGHT > 1920)
	{
		print_error(SCREEN_ERROR);
		exit(1);
	}
}

void	data(t_engine *eng, char **av)
{
	init_data(eng, (const char *)av[1]);
	get_file_data(eng);
	check_data_error(eng);
	check_text_file_error(eng);
}

int	main(int ac, char **av)
{
	t_engine	eng;
	char		*first;

	check_screen_error();
	first = malloc(sizeof(char));
	if (!first)
		quit_error_no_free(MALLOC_ERROR);
	eng.garbage_coll = ft_lstnew(first);
	eng.map_data = ft_malloc(sizeof(t_map_data), eng.garbage_coll);
	eng.mlx_data = ft_malloc(sizeof(t_win), eng.garbage_coll);
	eng.cal = ft_malloc(sizeof(t_calcul_data), eng.garbage_coll);
	check_error(ac, av, eng.garbage_coll);
	eng.size_file_content = count_file_line((const char *)av[1],
			eng.garbage_coll);
	eng.file_content = ft_malloc(sizeof(char *)
			* (eng.size_file_content + 1), eng.garbage_coll);
	data(&eng, av);
	find_map(&eng);
	if (!check_map((const char **)eng.map_data->map))
		quit_error(MAP_ERROR, eng.garbage_coll);
	play(&eng);
	if (eng.garbage_coll)
		clear(eng.garbage_coll);
	return (0);
}
