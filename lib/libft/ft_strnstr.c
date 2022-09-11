/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 17:33:05 by abahmani          #+#    #+#             */
/*   Updated: 2021/01/17 09:47:11 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		j;
	size_t		k;

	i = 0;
	k = 0;
	if (!*needle)
		return (haystack);
	while (haystack[i] && i < len)
	{
		j = i;
		while (haystack[j] && haystack[j] == needle[k] && j++ < len)
			k++;
		if (!needle[k])
			return (haystack + i);
		else
		{
			k = 0;
			i++;
		}
	}
	return (NULL);
}
