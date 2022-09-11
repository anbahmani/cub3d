/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 17:57:42 by abahmani          #+#    #+#             */
/*   Updated: 2021/06/12 18:18:53 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_malloc(unsigned int start, size_t len, size_t size)
{
	char	*ptr;

	if (size > start)
	{
		if ((size_t)(size - start + 1) < len)
			ptr = malloc((size - start + 1) * sizeof(char));
		else
			ptr = malloc((len + 1) * sizeof(char));
	}
	else
		ptr = malloc(sizeof(char));
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	size_t	i;
	char	*ptr;

	size = ft_strlen(s);
	i = 0;
	if (!s)
		return (0);
	ptr = ft_malloc(start, len, size);
	if (!ptr)
		return (NULL);
	while (start + i < size && s[start + i] && i < len)
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
