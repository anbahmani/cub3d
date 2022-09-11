/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:57:03 by abahmani          #+#    #+#             */
/*   Updated: 2021/06/12 18:10:22 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*tsrc;
	unsigned char	*tdest;

	i = 0;
	tsrc = (unsigned char *)src;
	tdest = (unsigned char *)dest;
	while (i < n)
	{
		tdest[i] = tsrc[i];
		if (tsrc[i] == (unsigned char )c)
			return (dest + i + 1);
		i++;
	}
	return (NULL);
}
