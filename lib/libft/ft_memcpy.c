/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:56:16 by abahmani          #+#    #+#             */
/*   Updated: 2021/01/16 15:14:21 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const char		*tmp_src;
	unsigned char	*tmp_dest;
	size_t			i;

	if (dest == NULL && src == NULL)
		return (NULL);
	tmp_src = src;
	tmp_dest = dest;
	i = 0;
	while (i < n)
	{
		*tmp_dest = *tmp_src;
		tmp_dest++;
		tmp_src++;
		i++;
	}
	return (dest);
}
