/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 14:11:20 by abahmani          #+#    #+#             */
/*   Updated: 2022/10/14 17:13:20 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

//function made for test - TODO : del before pushing for evaluation
void	display_tab(char **split)
{
	int i = 0;

	while (split[i])
	{
		printf("split[%d] = \t%s\n", i, split[i]);
		i++;
	}
}

//function made for test - TODO : del before pushing for evaluation
void display_data(t_map_data data)
{
	printf("NO ->%s\n", data.north_text);
	printf("SO ->%s\n", data.south_text);
	printf("EA ->%s\n", data.east_text);
	printf("WE ->%s\n", data.west_text);
	printf("C ->%d, %d, %d %d\n", data.ceiling_rgb.red, data.ceiling_rgb.green, data.ceiling_rgb.blue, data.ceiling_rgb.color);
	printf("F ->%d, %d, %d\n", data.floor_rgb.red, data.floor_rgb.green, data.floor_rgb.blue);
}

int	main(int ac, char **av)
{
	t_engine	eng;
	char	*first;

	first = malloc(sizeof(char));
	if (!first)
		quit_error_no_free(MALLOC_ERROR);
	eng.garbage_coll = ft_lstnew(first);
	eng.map_data = ft_malloc(sizeof(t_map_data), eng.garbage_coll);
	eng.mlx_data = ft_malloc(sizeof(t_win), eng.garbage_coll);
	eng.cal = ft_malloc(sizeof(t_calcul_data), eng.garbage_coll);
	check_error(ac, av, eng.garbage_coll);
	get_file_data(av[1], eng.map_data, eng.garbage_coll);
	eng.mlx_data->mlx = mlx_init();
	check_text_file_error(&eng);
	mlx_destroy_display(eng.mlx_data->mlx);
	free(eng.mlx_data->mlx);
	find_map(av[1], eng.map_data, eng.garbage_coll);
	if (!check_map_closed((const char **)eng.map_data->map))
		quit_error(MAP_ERROR, eng.garbage_coll);
	display_tab(eng.map_data->map);
	display_data(*eng.map_data);
	play(&eng);
	if(eng.garbage_coll)
		clear(eng.garbage_coll);
	return (0);
}