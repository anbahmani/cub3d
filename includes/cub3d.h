/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 14:11:33 by abahmani          #+#    #+#             */
/*   Updated: 2022/09/26 18:55:39 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "../lib/minilibx/mlx.h"
# include <math.h>

#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_EXIT	17
#define screenWidth 1920
#define screenHeight 1080
#define texWidth 64
#define texHeight 64

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		*data;
	int		img_width;
	int		img_height;
	int		size_l;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_perso
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	double moveSpeed;
	double rotSpeed;
}				t_perso;

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
	int		**texture;
	int     re_buf;
	int		buf[screenHeight][screenWidth];
	t_perso perso;
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

int calcul(t_win *mlx);
void    print_line(t_win *data, int x, int y1, int y2, int color);
int	key_press(int key, t_win *mlx);
void	draw(t_win *mlx);
void	load_texture(t_win *mlx);
void	load_image(t_win *mlx, int *texture, char *path, t_data *data);

/* cub3d.c */

void	my_mlx_pixel_put(t_win *mlx, int x, int y, int color);
int	main_loop(t_win *mlx);

#endif