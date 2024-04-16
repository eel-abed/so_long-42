/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:16:45 by eel-abed          #+#    #+#             */
/*   Updated: 2024/04/16 18:33:34 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#include <MLX42.h>

// Define the structure for the game
typedef struct s_game
{
	void *mlx;
	void *win;
	int width;
	int height;
} t_game;

// Define the structure for the player
typedef struct s_player
{
	int x;
	int y;
} t_player;

// Define the structure for the map
typedef struct s_map
{
	char **grid;
	int width;
	int height;
} t_map;

#endif
