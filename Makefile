NAME        	=   cub3d

CC          	=   gcc #-fsanitize=address -g3

SRC_DIR			= 	$(shell find srcs -type d) \

INC_DIR			= 	$(shell find includes -type d) \
					$(shell find lib/libft -type d) \
					$(shell find lib/minilibx -type d) \


INCSDIR			=	includes

OBJ_DIR			=	obj

LIB_DIR			= lib/libft lib/minilibx

vpath %.c $(foreach dir, $(SRC_DIR), $(dir):)

# library -----------------------------------------------------------

SRC			= 	cub3d.c \
				get_next_line.c get_next_line_utils.c \
				get_file_data.c get_map.c garbage_collector.c str_tools.c \
				tab_tools.c digit_tools.c arg_error.c error.c \
				input_file_error.c map_element.c init_perso.c  \
				check_map_error.c \
				side_pers.c move.c wall.c raycasting.c texture_file_error.c \
				init_side_dist.c calcul.c key.c exec_load.c load.c


OBJ			=	$(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))

DEPS		= 	$(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.d))

# Compilation flags -------------------------------------------------

CFLAGS		=	-Wall -Wextra -Werror -I ${INCSDIR}  -g3

IFLAGS		=	$(foreach dir, $(LIB_DIR), -I $(dir))

LFLAGS		=	$(foreach dir, $(LIB_DIR), -L $(dir))

# main part ---------------------------------------------------------

all:
	@echo "\n___$(NAME) Setting___\n"
	@make  $(NAME)

install:
	@make -C lib/libft bonus
	@make -C lib/minilibx

re-install:
	@$(foreach dir, $(LIB_DIR), make -C $(dir) re;)

fclean-install:
	@make -C lib/libft fclean
	@make -C lib/minilibx clean

show:
	@echo "SRC :\n$(SRC)"
	@echo "OBJ :\n$(OBJ)"
	@echo "CFLAGS :\n$(CFLAGS)"
	@echo "IFLAGS :\n$(IFLAGS)"
	@echo "LFLAGS :\n$(LFLAGS)"
	@echo "\n-----\n"
	@echo "Compiling : \n$(CC) $(CFLAGS) $(OBJ) -o $(NAME)"

$(NAME): $(OBJ)
	@echo "-----\nCreating Binary File $@ ... \c"
	make install
	@$(CC) $(CFLAGS) $(LFLAGS) $^ -o $@ ./lib/libft/libft.a ./lib/minilibx/libmlx_Linux.a -lm -lXext -lX11
	@echo "DONE\n-----"

-include	${DEPS}

$(OBJ_DIR)/%.o : %.c
	@echo "Compiling $@ ... \c"
	@mkdir -p $(OBJ_DIR)
	@$(CC) -I ${INCSDIR} $(CFLAGS) $(IFLAGS) -c $< -o $@ 
	@echo "DONE"

re:	fclean all

clean:
	@echo "Deleting Objects Directory $(OBJ_DIR) ... \c"
	@$(foreach file, $(OBJ), rm -rf $(file))
	@echo "DONE\n-----"

fclean:	clean
	@echo "Deleting Binary File $(NAME) ... \c"
	@rm -f $(NAME)
	@echo "DONE\n-----"

.PHONY: all bonus show re clean flcean install re-install fclean-install