/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:16:45 by eel-abed          #+#    #+#             */
/*   Updated: 2024/04/14 15:50:32 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <mlx/mlx.h>

# define MAP_WIDTH 20
# define MAP_HEIGHT 15

typedef struct  s_game
{
    void        *mlx;
    void        *win;
    // Ajoute ici les variables nécessaires pour ton jeu
}               t_game;

typedef struct  s_map
{
    char        **map;
    // Ajoute ici les variables nécessaires pour représenter la carte
}               t_map;

// Prototypes des fonctions
int     read_map(const char *file, t_map *map);
void    render_map(t_game *game, t_map *map);
void    move_player(t_game *game, t_map *map, int direction);
void    free_map(t_map *map);

#endif
