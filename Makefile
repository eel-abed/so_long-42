# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/14 13:49:16 by eel-abed          #+#    #+#              #
#    Updated: 2024/06/29 23:38:27 by eel-abed         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := so_long

CC := gcc

CFLAGS := -Wall -Wextra -fsanitize=address -Werror -Iheaders/ -g

SOURCE := srcs/*.c
LIBRARY := -LMLX42/build -lmlx42 -I/Users/$(USER)/.brew/opt/glfw/include -L/Users/$(USER)/.brew/opt/glfw/lib/ -lglfw -framework OpenGL -framework AppKit
MLX42 := MLX42/build
OBJ := $(patsubst %.c,%.o,$(wildcard srcs/*.c get_next_line_42/*.c))

all:
	make -C $(MLX42)
	$(CC) $(CFLAGS) $(SOURCE) $(GETNEXTLINE) $(LIBRARY) -o $(NAME)

clean:
	rm -f $(OBJ)
	make -C $(MLX42) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
