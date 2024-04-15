/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:16:45 by eel-abed          #+#    #+#             */
/*   Updated: 2024/04/15 14:36:49 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "MLX42/include/MLX42/MLX42.h"

# define MAP_WIDTH 20
# define MAP_HEIGHT 15

# define UP 0
# define DOWN 1
# define LEFT 2
# define RIGHT 3

typedef struct  s_player
{
    int         x;
    int         y;
    int         items_collected;
}               t_player;

typedef struct  s_game
{
    void        *mlx;
    void        *win;
    t_player    player;
    int         moves;
    int         game_over;
}               t_game;

typedef struct  s_map
{
    char        **map;
}               t_map;

int     read_map(const char *file, t_map *map);
void    render_map(t_game *game, t_map *map);
void    move_player(t_game *game, t_map *map, int direction);
void    free_map(t_map *map);
int     is_map_valid(t_map *map);

#endif
