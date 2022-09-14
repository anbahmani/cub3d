/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 14:11:33 by abahmani          #+#    #+#             */
/*   Updated: 2022/09/14 16:39:32 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft.h"

typedef enum s_texture
{
	NO,
	SO,
	WE,
	EA,
}	t_texture;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		*colors;
}	t_img;

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

typedef struct s_ihm
{
	void	*mlx;
	void	*mlx_win;
	t_img	img;
}	t_ihm;

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

typedef struct s_engine
{
	t_map_data	map;
	t_ihm		mlx_data;
	t_list		garbage_coll;
}	t_engine;

/*-------------------------------GET NEXT LINE--------------------------------*/

int		get_next_line(int fd, char **line);
char	*ft_substr_gnl(char *s, unsigned int start, size_t len, int f);
char	*ft_strjoin_gnl(char *s1, char *s2);

/*-------------------------------ERROR CHECKING-------------------------------*/

void	print_error(char *msg);
int		check_error(int ac, char **av);
int		check_input_file_error(char const *file_name);
int		open_img_xpm(char *texture_name, t_engine *engine);
void	check_text_file_error(t_engine *engine);
void	quit_error(char *msg);
int		check_arg_number_error(int argc);


/*-----------------------------GARBAGE COLLECTOR------------------------------*/

void	ft_malloc(void	*content, size_t size, t_list *garb_coll);
void	clear(t_list *garbage_collector);

/*--------------------------------PARSING-------------------------------------*/

void	get_file_data(const char *file_name, t_map_data *data, t_list *garb_c);
void	get_file_data_bis(const char *file_name, t_map_data *data,
		t_list *garb_c, char *line);
char	**get_map(char *line, int start, const char *file_name);
void	get_text_file_name(char *line, t_map_data *data, t_texture text);
void	set_color(t_rgb *colors, char **split);
t_rgb	get_color(char *line, t_list *garb_coll);


/*----------------------------------UTILS-------------------------------------*/

int		composed_with(char *str, const char *set);
int		is_in_set(char c, const char *set);
int		count_str(char **tab);
void	clear_str_tab(char **tab);
void	trim_split(char **tab);

#endif