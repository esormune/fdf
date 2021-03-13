# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/23 16:14:25 by esormune          #+#    #+#              #
#    Updated: 2021/03/13 11:15:08 by esormune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = gcc

CFLAGS = -g -Wall -Wextra -Werror

# directories
SRC_DIR = ./src/
INC_DIR = ./includes/
OBJ_DIR = ./obj/
LIBFT_DIR = ./libft/
MLX_DIR = ./minilibx/

#source files
SRC_FILES = main.c fdf_init.c fdf_map.c fdf_error.c fdf_draw.c fdf_keys.c \
	fdf_morph.c fdf_party.c
OBJ_FILES = $(SRC_FILES:.c=.o)

#paths
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)
MLX = $(addprefix $(MLX_DIR), libmlx.a)

#link libft and minilibx
LNK = -L $(LIBFT_DIR) -lft -L $(MLX_DIR) -lmlx \
	-L /opt/X11/lib -l Xext -lX11 \
	-framework OpenGL -framework AppKit 

all: obj $(LIBFT) $(MLX) $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)
$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -I $(MLX_DIR) -I $(LIBFT_DIR) -I $(INC_DIR) \
		-o $@ -c $<
$(LIBFT):
	@make -C $(LIBFT_DIR)
$(MLX):
	@make -C $(MLX_DIR)

# compilation
$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(LNK) -lm -o $(NAME)
	@echo "$(NAME) compiled."

# cleaning rules
clean:
	@rm -Rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean
	@echo "Object files deleted."

fclean:
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "$(NAME) deleted."

# re
re: fclean all

# phony
.PHONY = clean fclean all re
