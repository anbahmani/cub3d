/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 09:33:54 by abahmani          #+#    #+#             */
/*   Updated: 2022/10/08 02:21:52 by abahmani         ###   ########.fr       */
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
	print_error(msg);
	t_list *tmp;
	tmp = garb_c;
	while (tmp)
	{
		tmp = tmp->next;
	}
	
	clear(garb_c);
	exit(1);
}


void	quit_error_no_free(char *msg)
{
	print_error(msg);
	exit(1);
}

int		check_error(int ac, char **av, t_list *garb_c)
{
	if (!check_arg_number_error(ac, garb_c)
		|| !check_input_file_error(av[1], garb_c))
		return (1);
	return (0);
}
