# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/14 13:49:16 by eel-abed          #+#    #+#              #
#    Updated: 2024/07/10 13:10:17 by eel-abed         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CFLAGS = -Wall -Werror -Wextra -g

RM = rm -f
CC = gcc

SRC = srcs/display_elem.c srcs/elements.c srcs/flood_fill.c srcs/free.c \
        srcs/handle_elements.c srcs/height_width.c srcs/hooks.c srcs/map.c \
        srcs/openfile.c srcs/so_long.c

OBJ = $(SRC:.c=.o)

MLX42_REPO = https://github.com/codam-coding-college/MLX42.git
MLX42_DIR = MLX42
MLX42_BUILD_DIR = $(MLX42_DIR)/build
MLX42_LIB = $(MLX42_BUILD_DIR)/libmlx42.a

USER = $(shell whoami)

HEADERS_MLX42 = $(MLX42_DIR)/include/MLX42
HEADERS_GLFW = /Users/$(USER)/homebrew/opt/glfw/lib

all: $(LIBFT_LIB) mlx42 $(NAME)

mlx42 :
		@git clone $(MLX42_REPO) $(MLX42_DIR)
		@cd $(MLX42_DIR) && cmake -B build
		@cd $(MLX42_DIR) && cmake --build build -j4

%.o: %.c
	$(CC) $(CFLAGS) -I. -I$(HEADERS_MLX42) -I$(HEADERS_GLFW) -c $< -o $@ 

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -I. -I$(HEADERS_MLX42) -L$(HEADERS_GLFW) -L$(MLX42_BUILD_DIR) -lmlx42 -ldl -lglfw -pthread -lm  -framework Cocoa -framework OpenGL -framework IOKit -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
