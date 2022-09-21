NAME        	=   cub3d

CC          	=   gcc

SRC_DIR			= 	$(shell find srcs -type d)
INC_DIR			= 	$(shell find includes -type d) \
					#$(shell find lib/libft -type d) \

OBJ_DIR			=	obj

LIB_DIR			=	lib/minilibx lib/libft

vpath %.c $(foreach dir, $(SRC_DIR), $(dir):)

# library -----------------------------------------------------------

SRC			= 	cub3d.c \
				ray_casting.c \

OBJ			=	$(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))

# Compilation flags -------------------------------------------------

CFLAGS		=	-Wall -Wextra -Werror -pthread #-g3 -fsanitize=thread

IFLAGS		=	$(foreach dir, $(INC_DIR), -I $(dir))

# main part ---------------------------------------------------------

install:
	@$(foreach dir, $(LIB_DIR), make -C $(dir);)

re-install:
	@$(foreach dir, $(LIB_DIR), make -C $(dir) re;)

fclean-install:
	@make -C lib/libft fclean

all:
	@echo "\n___$(NAME) Setting___\n"
	@make  $(NAME)

bonus: fclean
	@echo "\n___$(NAME) Setting___\n"
	@make $(NAME_BONUS)

show:
	@echo "SRC :\n$(SRC)"
	@echo "OBJ :\n$(OBJ)"
	@echo "CFLAGS :\n$(CFLAGS)"
	@echo "IFLAGS :\n$(IFLAGS)"
	@echo "\n-----\n"
	@echo "Compiling : \n$(CC) $(CFLAGS)  $(OBJ)  -o $(NAME)"

$(NAME): install $(OBJ)
	@echo "-----\nCreating Binary File $@ ... \c"
	
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)   ./lib/minilibx/libmlx_Linux.a -L./lib/minilibx -lm -lXext -lX11 
	@echo "DONE\n-----"

$(OBJ_DIR)/%.o : %.c
	@echo "Compiling $@ ... \c"
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<
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