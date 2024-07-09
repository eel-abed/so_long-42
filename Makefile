# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/14 13:49:16 by eel-abed          #+#    #+#              #
#    Updated: 2024/07/09 15:03:41 by eel-abed         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := so_long

CC := gcc

CFLAGS := -Wall -Wextra -Werror -Iheaders/ -g

SRCS := srcs/display_elem.c srcs/elements.c srcs/flood_fill.c srcs/free.c \
        srcs/handle_elements.c srcs/height_width.c srcs/hooks.c srcs/map.c \
        srcs/openfile.c srcs/so_long.c
OBJS := $(SRCS:.c=.o)

LIBRARY := -LMLX42/build -lmlx42 -I/Users/$(USER)/.brew/opt/glfw/include -L/Users/$(USER)/.brew/opt/glfw/lib/ -lglfw -framework OpenGL -framework AppKit
MLX42 := MLX42/build

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(MLX42)
	$(CC) $(CFLAGS) $(OBJS) $(LIBRARY) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(MLX42) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
