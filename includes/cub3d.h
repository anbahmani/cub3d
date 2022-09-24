/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 14:11:33 by abahmani          #+#    #+#             */
/*   Updated: 2022/09/24 06:23:15 by abahmani         ###   ########.fr       */
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
# include "mlx.h"

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

/*-------------------------------KEY EVENT DEFINE-----------------------------*/

# define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_EXIT	17

/*-------------------------------MAP DATA DEFINE------------------------------*/
/*
# define mapWidth 24
# define mapHeight 24
# define width 1920
# define height 1080
*/
/*----------------------------SCREEN DATA DEFINE------------------------------*/

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080

/*----------------------------PERSO CONFIG DEFINE-----------------------------*/

# define PERSO_MOVEMENT_SPEED 0.17
# define PERSO_ROTATION_SPEED 0.14
# define PERSO_PLANE_X 0
# define PERSO_PLANE_Y 0.66

/*---------------------------------STRUCTURE----------------------------------*/

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		*colors;
}	t_img;

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
} t_perso;

typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
}	t_rgb;

/*
typedef struct s_ihm
{
	void	*mlx;
	void	*mlx_win;
	t_img	img;
}	t_ihm;
*/

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
	t_perso	player;
}	t_map_data;

typedef struct s_engine
{
	t_map_data	*map_data;
	t_win		*mlx_data;
	t_list		*garbage_coll;
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
int		check_arg_number_error(int argc, t_list *garb_c);


/*-----------------------------GARBAGE COLLECTOR------------------------------*/

void	*ft_malloc(size_t size, t_list *garb_coll);
void	clear(t_list *garbage_collector);

/*--------------------------------PARSING-------------------------------------*/

void	get_file_data(const char *file_name, t_map_data *data, t_list *garb_c);
void	get_file_data_bis(t_map_data *data, t_list *garb_c, char *line);
char	**get_map(int start, const char *file_name, t_list *garb_c);
void	find_map(const char *file_name, t_map_data *data, t_list *garb_c);
int		is_map_line(char *line);
void	set_color(t_rgb *colors, char **split);
t_rgb	get_color(char *line, t_list *garb_coll);
void	set_color(t_rgb *colors, char **split);
int		count_file_line(char const *file_name, t_list *garb_c);

/*--------------------------------RAYCASTING----------------------------------*/

int		calcul(t_win *mlx);
void	print_line(t_win *data, int x, int y1, int y2, int color);
int		key_press(int key, t_win *mlx);

/*------------------------------------IHM-------------------------------------*/

void	my_mlx_pixel_put(t_win *mlx, int x, int y, int color);
void	init_ihm(t_win *mlx_data);
int		main_loop(t_engine eng);

/*----------------------------------UTILS-------------------------------------*/

int		composed_with(char *str, const char *set);
int		is_in_set(char c, const char *set);
int		count_str(char **tab);
void	clear_str_tab(char **tab);
void	trim_split(char **tab);
char	*ft_str_dup_cub(char *str, t_list *garb_c);
int		is_orientation_char(char c);


//Function for test


void	display_tab(char	**split);

#endif