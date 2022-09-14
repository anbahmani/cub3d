/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:53:59 by abahmani          #+#    #+#             */
/*   Updated: 2022/09/14 11:09:24 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_in_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if ((char)set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	composed_with(char *str, const char *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (!is_in_set(str[i], set))
			return (0);
	}
	return (1);
}
