/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 14:11:33 by abahmani          #+#    #+#             */
/*   Updated: 2022/09/21 17:50:14 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "../lib/minilibx/mlx.h"
# include <math.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_win
{
	void	*mlx;
	void	*mlx_win;
	void	*mlx_img;
	int		height;
	int		width;
	char	*str;
	int		size;
	int		height_map;
	int		width_map;
	t_data	data;
}	t_win;


typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
}	t_rgb;

typedef struct s_map_data
{
	char	**map;
	int		width;
	int		height;
	char	*north_text;
	char	*south_text;
	char	*east_text;
	char	*west_text;
	t_rgb	floor_rgb;
	t_rgb	ceiling_rgb;
	t_pos	player;
}	t_map_data;

int		get_next_line(int fd, char **line);
char	*ft_substr_gnl(char *s, unsigned int start, size_t len, int f);
char	*ft_strjoin_gnl(char *s1, char *s2);

/* ray_casting.c*/

int main_loop(void);

#endif