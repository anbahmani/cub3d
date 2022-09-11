/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 17:30:52 by abahmani          #+#    #+#             */
/*   Updated: 2021/06/12 18:18:16 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*tmp_last;
	const char	*tmp;

	tmp_last = s;
	tmp = s;
	while (*tmp)
	{
		if (*tmp == (char)c)
		{
			tmp_last = tmp;
		}
		tmp++;
	}
	if (*tmp_last == (char)c)
		return ((char *)tmp_last);
	else if ((char)c == '\0')
		return ((char *)tmp);
	else
		return (NULL);
}
