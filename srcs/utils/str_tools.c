/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:53:59 by abahmani          #+#    #+#             */
/*   Updated: 2022/10/14 20:26:27 by raaga            ###   ########.fr       */
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

	i = 0;
	while (str[i])
	{
		if (!is_in_set(str[i], set))
			return (0);
		i++;
	}
	return (1);
}

//maybe unused
char	*ft_str_dup_cub(char *str, t_list *garb_c)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_malloc(sizeof(char) * ft_strlen(str) + 1, garb_c);
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
