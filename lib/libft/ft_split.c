/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 09:28:35 by abahmani          #+#    #+#             */
/*   Updated: 2021/12/01 14:46:25 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_str(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i + 1] && s[i] == c && s[i + 1] != c)
			count++;
		if (i == 0 && s[i] != c)
			count++;
		i++;
	}
	return (count);
}

static	void	clear_tab(char **tab, size_t size)
{
	size_t	i;

	i = 0;
	while (tab[i] && i < size)
		free(tab[i++]);
	free(tab);
}

static char	*split_str(char const *s, char c, size_t begin)
{
	size_t	i;
	size_t	j;
	size_t	count;
	char	*str;

	i = begin;
	j = 0;
	count = 0;
	while (s[begin] && s[begin++] != c)
	{
		count++;
	}
	str = malloc(sizeof(char) * (count) + 1);
	if (!str)
		return (NULL);
	while (s[i] && s[i] != c)
	{
		str[j++] = s[i++];
	}
	str[j] = '\0';
	return (str);
}

static	char	**fill_str(char const *s, char c, size_t nb_str, char **tab_str)
{
	size_t	j;
	size_t	i;

	j = 0;
	i = 0;
	while (j < nb_str)
	{
		if (s[i] != c)
		{
			tab_str[j] = split_str(s, c, i);
			if (tab_str[j] == NULL)
			{
				clear_tab(tab_str, nb_str);
				return (NULL);
			}
			i += ft_strlen(tab_str[j++]);
		}
		else
			i++;
	}
	return (tab_str);
}

char	**ft_split(char const *s, char c)
{
	size_t	nb_str;
	char	**tab_str;

	if (!s)
		return (0);
	nb_str = count_str(s, c);
	tab_str = malloc(sizeof(char *) * (nb_str + 1));
	if (!tab_str)
		return (NULL);
	tab_str[nb_str] = NULL;
	if (nb_str == 1)
		tab_str[0] = ft_strtrim(s, &c);
	else if (!fill_str(s, c, nb_str, tab_str))
		return (NULL);
	return (tab_str);
}
