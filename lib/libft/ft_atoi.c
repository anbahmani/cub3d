/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 18:28:27 by abahmani          #+#    #+#             */
/*   Updated: 2021/06/12 18:06:52 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	pass_isspace(const char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
	{
		i++;
	}
	return (i);
}

static	int	find_signe(const char *str, int i)
{
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (0);
		else
			return (2);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	signe;
	int	nb;

	i = pass_isspace(str);
	signe = find_signe(str, i);
	nb = 0;
	if (signe == 0 || signe == 2)
	{
		signe--;
		i++;
	}
	while (ft_isdigit((int)str[i]))
	{
		nb = (nb + (str[i] - 48) * signe);
		if (str[i + 1] && ft_isdigit(str[i + 1]))
			nb *= 10;
		if (nb < 0 && signe == 1)
			return (-1);
		if (nb > 0 && signe == -1)
			return (0);
		i++;
	}
	return (nb);
}
