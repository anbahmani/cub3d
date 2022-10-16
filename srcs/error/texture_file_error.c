/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_file_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 18:00:05 by abahmani          #+#    #+#             */
/*   Updated: 2022/10/16 19:40:10 by abahmani         ###   ########.fr       */
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
	}
	else if (height != TEX_HEIGHT || width != TEX_WIDTH)
	{
		msg = ft_strjoin(SIZE_TEXTURE_ERROR, texture_name);
		ft_lstadd_back(&engine->garbage_coll, ft_lstnew(msg));
	}
	if (tmp)
		mlx_destroy_image(engine->mlx_data->mlx, tmp);
	if (!tmp || height != TEX_HEIGHT || width != TEX_WIDTH)
	{
		mlx_destroy_display(engine->mlx_data->mlx);
		free(engine->mlx_data->mlx);
		quit_error(msg, engine->garbage_coll);
	}
}

static int	check_texture_file_name(char const *file_name)
{
	unsigned int	len;

	if (!file_name)
		return (0);
	len = (int)ft_strlen(file_name);
	if (len < 5)
		return (0);
	if (file_name[len - 1] != 'm'
		|| file_name[len - 2] != 'p'
		|| file_name[len - 3] != 'x'
		|| file_name[len - 4] != '.'
		|| file_name[len - 5] == '/')
		return (0);
	return (1);
}

void	check_text_file_error(t_engine *engine)
{
	engine->mlx_data->mlx = mlx_init();
	if (!check_texture_file_name((const char *)engine->map_data->north_text)
		|| !check_texture_file_name((const char *)engine->map_data->south_text)
		|| !check_texture_file_name((const char *)engine->map_data->west_text)
		|| !check_texture_file_name((const char *)engine->map_data->east_text))
	{
		mlx_destroy_display(engine->mlx_data->mlx);
		free(engine->mlx_data->mlx);
		quit_error(TEXTURE_FILE_NAME_ERROR, engine->garbage_coll);
	}
	open_img_xpm(engine->map_data->north_text, engine);
	open_img_xpm(engine->map_data->south_text, engine);
	open_img_xpm(engine->map_data->east_text, engine);
	open_img_xpm(engine->map_data->west_text, engine);
	mlx_destroy_display(engine->mlx_data->mlx);
	free(engine->mlx_data->mlx);
}
