/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 10:44:44 by abahmani          #+#    #+#             */
/*   Updated: 2021/11/06 19:22:57 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	isinset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static	char	*empty_str(void)
{
	char	*str;

	str = malloc(sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '\0';
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		i;
	size_t		j;

	if (!s1 || !set)
		return (0);
	i = 0;
	j = ft_strlen(s1);
	if (j != 0)
		j--;
	while (i < j && (isinset(s1[i], set) || isinset(s1[j], set)))
	{
		if (isinset(s1[i], set))
			i++;
		if (isinset(s1[j], set))
			j--;
	}
	if (j <= i)
		return (empty_str());
	return (ft_substr(s1, i, j - i + 1));
}
