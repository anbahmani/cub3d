/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 17:56:12 by abahmani          #+#    #+#             */
/*   Updated: 2022/09/11 17:56:26 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_arg_number_error(int argc)
{
	if (argc != 2)
	{
		print_error("Le nombre d'arguments est incorrectes.");
		return (0);
	}
	return (1);
}
