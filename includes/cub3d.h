/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 14:11:33 by abahmani          #+#    #+#             */
/*   Updated: 2022/10/16 19:38:26 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <strings.h>
# include "../lib/libft/libft.h"
# include "../lib/minilibx/mlx.h"

/*-------------------------------ERROR DEFINE---------------------------------*/

# define FD_ERROR "An error occured during the file opening."
# define MALLOC_ERROR "An error occured during the memory allocation."
# define TOO_MUCH_ARG_ERROR "There is too much argument."
# define TOO_FEW_ARG_ERROR "There is too few argument."
# define INCORRECT_FILE_NAME_ERROR "The input file name is incorrect."
# define FILE_NOT_EXIST_ERROR "The input file does not exist."
# define FILE_IS_DIR_ERROR "The input file is a directory."
# define FILE_IS_SYM_LINK "The input file is a symbolic link."
# define TEXTURE_FILE_ERROR "This texture file is not correctly filled : "
# define COLOR_ERROR "The colors from the file are not correctly written."
# define MAP_ERROR "The map from the file is incorrectly filled."
# define DOUBLON_TEXTURE_ERROR "A texture is in double."
# define TEXTURE_FILE_NAME_ERROR "Incorrect texture file name."
# define SCREEN_ERROR "The size of the screen is incorrect."
# define SIZE_TEXTURE_ERROR "The size of this texture is incorrect : "
# define DOUBLON_COLOR_ERROR "A color is in double."

/*-------------------------------KEY EVENT DEFINE-----------------------------*/

# define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_EXIT	17

/*-------------------------------TEXTURE SIZE DEFINE--------------------------*/

# define TEX_WIDTH 64
# define TEX_HEIGHT 64

/*-------------------------------MAP DATA DEFINE------------------------------*/
/*
# define mapWidth 24
# define mapHeight 24
# define width 1920
# define height 1080
*/
/*----------------------------SCREEN DATA DEFINE------------------------------*/

# define SCREEN_WIDTH 1080
# define SCREEN_HEIGHT 720

/*----------------------------PERSO CONFIG DEFINE-----------------------------*/

# define PERSO_MOVEMENT_SPEED 0.071
# define PERSO_ROTATION_SPEED 0.0351

/*---------------------------------STRUCTURE----------------------------------*/

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		*data;
	int		img_width;
	int		img_height;
	int		size_l;
	int		bpp;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_win
{
	int		color;
	int		up;
	int		down;
	int		right;
	int		left;
	int		left_pers;
	int		right_pers;
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
	int		re_buf;
	int		buf[SCREEN_HEIGHT][SCREEN_WIDTH];
	t_data	data;
}	t_win;

typedef struct s_pos_int
{
	int	x;
	int	y;
}	t_pos_int;

typedef struct s_perso
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
}	t_perso;

typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
	int	color;
	int	init;
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
	int		doublon_text;
	t_rgb	floor_rgb;
	t_rgb	ceiling_rgb;
	t_perso	player;
}	t_map_data;

typedef struct s_calcul_data
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	double	wall_x;
	int		tex_num;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		draw_start;
	int		draw_end;
}	t_calcul_data;

typedef struct s_engine
{
	t_map_data		*map_data;
	t_win			*mlx_data;
	t_calcul_data	*cal;
	t_list			*garbage_coll;
	char			**file_content;
	int				size_file_content;
}	t_engine;

/*-------------------------------GET NEXT LINE--------------------------------*/

int		get_next_line(int fd, char **line);
char	*ft_substr_gnl(char *s, unsigned int start, size_t len, int f);
char	*ft_strjoin_gnl(char *s1, char *s2);

/*-------------------------------ERROR CHECKING-------------------------------*/

void	print_error(char *msg);
int		check_error(int ac, char **av, t_list *garb_c);
int		check_input_file_error(char const *file_name, t_list *garb_c);
void	check_text_file_error(t_engine *engine);
void	quit_error(char *msg, t_list *garb_c);
void	quit_error_no_free(char *msg);
int		check_arg_number_error(int argc, t_list *garb_c);
int		check_number_player(char **map);
int		check_map(const char **map);
void	check_data_error(t_engine *eng);

/*-----------------------------GARBAGE COLLECTOR------------------------------*/

void	*ft_malloc(size_t size, t_list *garb_coll);
void	clear(t_list *garbage_collector);

/*--------------------------------PARSING-------------------------------------*/

void	get_file_data(t_engine *eng);
void	get_file_data_bis(t_engine *eng, char *line);
char	**get_map(int start, t_engine *eng);
void	find_map(t_engine *eng);
int		is_map_line(char *line);
void	set_color(t_rgb *colors, char **split, t_engine *eng);
t_rgb	get_color(char *line, t_engine *eng);
int		count_line_map(int start, t_engine *eng);
void	init_perso(t_engine *eng);
void	test_color(t_engine *eng, char **split);
void	check_trim_color(char *str, t_engine *eng);
void	init_color(t_engine *eng, char *line, t_rgb *rgb);
int		count_file_line(char const *file_name, t_list *garb_c);
void	get_file_content(t_engine *eng, const char *file_name);

/*--------------------------------RAYCASTING----------------------------------*/

int		calcul(t_engine *eng, int x);
int		key_press(int key, t_engine *engine);
int		key_release(int key, t_engine *eng);
void	play(t_engine *eng);
void	draw(t_engine *eng);
void	exec_load(t_engine *eng);
void	load_texture(t_engine *eng);
void	load_image(t_engine *eng, int *texture, char *path, t_data *data);
void	init_side_dist(t_engine *eng);
void	wall_detect(t_engine *eng);
void	calcul_dist_wall(t_engine *eng);
void	init_var(t_engine *eng, int x);
void	wall_draw(t_engine *eng, int x, int y, int z);
void	ceiling_or_floor(t_engine *eng, int x, int q);
int		get_move(t_engine *eng);
void	right_pers(t_engine *eng);
void	left_pers(t_engine *eng);
void	move_up(t_engine *eng);
void	move_down(t_engine *eng);
void	move_left(t_engine *eng);
void	move_right(t_engine *eng);

/*------------------------------------IHM-------------------------------------*/

void	init_ihm(t_win *mlx_data);
void	ft_destroy_mlx(t_win *mlx_data);

/*----------------------------------UTILS-------------------------------------*/

int		composed_with(char *str, const char *set);
int		is_in_set(char c, const char *set);
int		count_str(char **tab);
void	clear_str_tab(char **tab);
void	trim_split(char **tab);
char	*ft_str_dup_cub(char *str, t_list *garb_c);
int		is_orientation_char(char c);
void	fill_map(t_map_data *data, t_list *garb_c);

#endif