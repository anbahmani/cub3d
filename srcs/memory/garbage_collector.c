/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 11:02:01 by abahmani          #+#    #+#             */
/*   Updated: 2022/09/14 19:14:30 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_malloc(size_t size, t_list *garb_coll)
{
	void	*content;

	content = malloc(sizeof(size));
	ft_lstadd_back(&garb_coll, ft_lstnew(content));
	return (content);
}

void	clear(t_list *garbage_collector)
{
	ft_lstclear(&garbage_collector, &free);
}
