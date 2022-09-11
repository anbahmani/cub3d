/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 18:24:04 by abahmani          #+#    #+#             */
/*   Updated: 2021/01/16 14:03:56 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	n;
	char	*ptr;

	n = ft_strlen(s1);
	ptr = malloc((n + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	return (ft_memmove(ptr, s1, n + 1));
}
