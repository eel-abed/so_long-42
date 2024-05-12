/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:40:33 by eel-abed          #+#    #+#             */
/*   Updated: 2024/05/12 17:06:00 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"



void ft_hook(void* param)
{
    mlx_t* mlx = param;
    unsigned int new_x = player->instances[0].x;
    unsigned int new_y = player->instances[0].y;

    if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		new_y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		new_y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		new_x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		new_x += 5;
		
	// Check if the new position collides with any of the obstacles
	for (size_t i = 0; i < obstacle->count; i++) {
		if (!(new_x + player->width < (unsigned int)obstacle->instances[i].x || new_x > (unsigned int)obstacle->instances[i].x + 64 ||
			  new_y + player->height < (unsigned int)obstacle->instances[i].y || new_y > (unsigned int)obstacle->instances[i].y + 64)) {
			// New position collides with an obstacle, do not move
			return;
		}
	}
	
	// Check if it is within the window boundaries
	if (new_x >= 0 && new_x <= (unsigned int)mlx->width && new_y >= 0 && new_y <= (unsigned int)mlx->height) {
		player->instances[0].x = new_x;
		player->instances[0].y = new_y;
	}	
}
