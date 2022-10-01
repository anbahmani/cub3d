/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_file_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 18:00:05 by abahmani          #+#    #+#             */
/*   Updated: 2022/10/01 04:06:23 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	open_img_xpm(char *texture_name, t_engine *engine)
{
	void	*tmp;
	int		width;
	int		height;
	char	*msg;

	tmp = mlx_xpm_file_to_image(engine->mlx_data->mlx, texture_name,
			&height, &width);
	if (!tmp)
	{
		msg = ft_strjoin(TEXTURE_FILE_ERROR, texture_name);
		ft_lstadd_back(&engine->garbage_coll, ft_lstnew(msg));
		quit_error(msg, engine->garbage_coll);
	}
	mlx_destroy_image(engine->mlx_data->mlx, tmp);
}

void	check_text_file_error(t_engine *engine)
{
	open_img_xpm(engine->map_data->north_text, engine);
	open_img_xpm(engine->map_data->south_text, engine);
	open_img_xpm(engine->map_data->east_text, engine);
	open_img_xpm(engine->map_data->west_text, engine);
}
