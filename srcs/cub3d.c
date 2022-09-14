/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 14:11:20 by abahmani          #+#    #+#             */
/*   Updated: 2022/09/14 16:30:03 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
int	main(int ac, char **av)
{
	t_map_data data;
	t_list gc;
(void)ac;
	get_file_data(av[1], &data, &gc);
	printf("NO ->%s\n", data.north_text);
	printf("SO ->%s\n", data.south_text);
	printf("EA ->%s\n", data.east_text);
	printf("WE ->%s\n", data.west_text);
	printf("C ->%d, %d, %d\n", data.ceiling_rgb.red, data.ceiling_rgb.green, data.ceiling_rgb.blue);
	printf("F ->%d, %d, %d\\n", data.floor_rgb.red, data.floor_rgb.green, data.floor_rgb.blue);
	return (0);
}