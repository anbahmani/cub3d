/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digit_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 10:08:21 by abahmani          #+#    #+#             */
/*   Updated: 2022/09/14 11:10:06 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//WARNING : maybe not used
int	digit_count(int nb)
{
	int	digit;

	digit = 0;
	while (nb)
	{
		nb /= 10;
		digit++;
	}
	return (digit);
}
