/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 17:56:12 by abahmani          #+#    #+#             */
/*   Updated: 2022/10/01 03:35:26 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_arg_number_error(int argc, t_list *garb_c)
{
	if (argc < 2)
	{
		quit_error(TOO_FEW_ARG_ERROR, garb_c);
		return (0);
	}
	else if (argc > 2)
	{
		quit_error(TOO_MUCH_ARG_ERROR, garb_c);
		return (0);
	}
	return (1);
}
