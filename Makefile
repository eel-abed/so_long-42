# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/14 13:49:16 by eel-abed          #+#    #+#              #
#    Updated: 2024/04/17 17:29:02 by eel-abed         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := so_long

CC := gcc

CFLAGS := -Wall -Wextra -Werror -Iheaders/

SOURCE := srcs/*.c
GETNEXTLINE := get_next_line_42/*c
LIBRARY := -L/Users/eel-abed/Documents/Ecole42/so_long/ -L/Users/eel-abed/.brew/opt/glfw/lib -lmlx42 -lglfw -framework OpenGL -framework AppKit
MLX42 := MLX42/build/

all:
	make -C $(MLX42)
	$(CC) $(CFLAGS) $(SOURCE) $(GETNEXTLINE) $(LIBRARY) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
