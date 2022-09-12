/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_file_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 18:00:05 by abahmani          #+#    #+#             */
/*   Updated: 2022/09/12 09:52:54 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	open_img_xpm(char *texture_name, t_engine *engine)
{
	void	*tmp;
	int		width;
	int		height;
	char	*msg;

	tmp = mlx_xpm_file_to_image(engine->mlx_data.mlx, texture_name,
			&height, &width);
	if (!tmp)
	{
		msg = ft_strjoin("Le fichier texture est errone : ", texture_name);
		print_error(msg);
		free(msg);
		return (0);
	}
	mlx_destroy_image(engine->mlx_data.mlx, tmp);
	return (1);
}

void	check_text_file_error(t_engine *engine)
{
	if (!open_img_xpm(engine->map.north_text, engine)
		|| !open_img_xpm(engine->map.south_text, engine)
		|| !open_img_xpm(engine->map.east_text, engine)
		|| !open_img_xpm(engine->map.west_text, engine))
	{
		end_game(engine);
	}
}
