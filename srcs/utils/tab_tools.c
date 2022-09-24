/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 10:45:20 by abahmani          #+#    #+#             */
/*   Updated: 2022/09/24 01:36:40 by abahmani         ###   ########.fr       */
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
		tab[i] = ft_strtrim(tab[i], " \t");
		free(tmp);
		i++;
	}
}

char	**ft_tabncpy(char **tab, int n, t_list *garb_c)
{
	int		i;
	char	**new_tab;

	i = 0;
	new_tab = ft_malloc(sizeof(char*) * n, garb_c);
	while (tab[i] && i < n)
	{
		new_tab[i] = tab[i];
		i++;
	}
	return (new_tab);
}

void	del_last_empty_str(char **tab, t_list *garb_c)
{
	int	i;
	int	nb_str;
	int	empty_str;
	
	nb_str = count_str(tab);
	i = nb_str - 1;
	empty_str = 0;
	while (i)
	{
		if (tab[i][0])
			break;
		empty_str++;
		i--;
	}
	tab = ft_tabncpy(tab, nb_str - empty_str, garb_c);
}

