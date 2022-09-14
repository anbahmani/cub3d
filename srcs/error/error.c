/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 09:33:54 by abahmani          #+#    #+#             */
/*   Updated: 2022/09/14 19:30:20 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

void	quit_error(char *msg, t_list *garb_c)
{
	clear(garb_c);
	print_error(msg);
	exit(1);
}

int		check_error(int ac, char **av)
{
	if (!check_arg_number_error(ac) || !check_input_file_error(av[1]))
		return (1);
	return (0);
}
