/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 11:02:01 by abahmani          #+#    #+#             */
/*   Updated: 2022/10/08 02:27:35 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_destroy_mlx(t_win *mlx_data)
{
	mlx_destroy_image(mlx_data->mlx, mlx_data->data.img);
	mlx_destroy_window(mlx_data->mlx, mlx_data->mlx_win);
	mlx_destroy_display(mlx_data->mlx);
	free(mlx_data->mlx);
}

void	*ft_malloc(size_t size, t_list *garb_coll)
{
	void	*content;

	content = malloc(size);
	if (!content)
		quit_error(MALLOC_ERROR, garb_coll);
	ft_lstadd_back(&garb_coll, ft_lstnew(content));
	return (content);
}

void	clear(t_list *garbage_collector)
{
	ft_lstclear(&garbage_collector, &free);
}
