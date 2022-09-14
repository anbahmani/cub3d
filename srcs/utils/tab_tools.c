/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 10:45:20 by abahmani          #+#    #+#             */
/*   Updated: 2022/09/14 11:07:59 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_str(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	clear_str_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	trim_split(char **tab)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tab[i])
	{
		tmp = tab[i];
		tab[i] = ft_strtrim(tab[i]);
		free(tmp);
		i++;
	}
}
