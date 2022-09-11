/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 14:02:22 by abahmani          #+#    #+#             */
/*   Updated: 2021/06/12 18:07:49 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	digit_count(int n)
{
	size_t	count;
	int		nb;

	count = 0;
	nb = n;
	if (n == 0)
		return (1);
	while (nb)
	{
		nb /= 10;
		count++;
	}
	if (n < 0)
		count++;
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	i;

	i = digit_count(n);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	str[i--] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n != 0)
	{
		if (n < 0)
			str[i--] = (n % 10) * (-1) + '0';
		else
			str[i--] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
