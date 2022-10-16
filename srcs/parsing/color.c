/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:45:40 by abahmani          #+#    #+#             */
/*   Updated: 2022/10/16 19:37:58 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_color(t_rgb *colors, char **split, t_engine *eng)
{
	colors->red = ft_atoi((const char *)split[0]);
	colors->green = ft_atoi((const char *)split[1]);
	colors->blue = ft_atoi((const char *)split[2]);
	clear_str_tab(split);
	if (colors->red < 0 || colors->red > 255)
		quit_error(COLOR_ERROR, eng->garbage_coll);
	if (colors->green < 0 || colors->green > 255)
		quit_error(COLOR_ERROR, eng->garbage_coll);
	if (colors->blue < 0 || colors->blue > 255)
		quit_error(COLOR_ERROR, eng->garbage_coll);
	colors->init = 1;
}

void	test_color(t_engine *eng, char **split)
{
	if (!composed_with(split[0], "0123456789") || !ft_strlen(split[0])
		|| !composed_with(split[1], "0123456789") || !ft_strlen(split[1])
		|| !composed_with(split[2], "0123456789") || !ft_strlen(split[2]))
	{
		clear_str_tab(split);
		quit_error(COLOR_ERROR, eng->garbage_coll);
	}
}

void	check_trim_color(char *str, t_engine *eng)
{
	char	*tmp;

	tmp = ft_strtrim(str + 2, " \t");
	if (!ft_isdigit(tmp[0]) || !ft_isdigit(tmp[ft_strlen(tmp) - 1]))
	{
		free(tmp);
		quit_error(COLOR_ERROR, eng->garbage_coll);
	}
	free(tmp);
}

void	init_color(t_engine *eng, char *line, t_rgb *rgb)
{
	if (rgb && rgb->init == 1)
		quit_error(DOUBLON_COLOR_ERROR, eng->garbage_coll);
	*rgb = get_color(line, eng);
	rgb->color = rgb->red * 65536;
	rgb->color += rgb->green * 256;
	rgb->color += rgb->blue;
}

t_rgb	get_color(char *line, t_engine *eng)
{
	t_rgb	*colors;
	char	**split;
	int		nb_str;

	check_trim_color(line, eng);
	split = ft_split(line + 2, ',');
	nb_str = count_str(split);
	if (nb_str > 3 || nb_str < 3)
	{
		clear_str_tab(split);
		quit_error(COLOR_ERROR, eng->garbage_coll);
	}
	trim_split(split);
	test_color(eng, split);
	colors = (t_rgb *)malloc(sizeof(t_rgb));
	ft_lstadd_back(&eng->garbage_coll, ft_lstnew(colors));
	if (!colors)
		quit_error(MALLOC_ERROR, eng->garbage_coll);
	set_color(colors, split, eng);
	return (*colors);
}
