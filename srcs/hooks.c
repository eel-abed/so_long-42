/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:40:33 by eel-abed          #+#    #+#             */
/*   Updated: 2024/05/28 19:11:01 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"


unsigned int total_movements = 0; // Global variable to keep track of total movements
unsigned int collectibles_taken = 0; // Global variable to keep track of collectibles taken

void ft_hook(void* param)
{
	mlx_t* mlx = param;
	unsigned int old_x = player->instances[0].x;
	unsigned int old_y = player->instances[0].y;
	
	unsigned int new_x = old_x;
	unsigned int new_y = old_y;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		new_y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		new_y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		new_x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		new_x += 5;
		
	// Check if the new position collides with any of the obstacles
	for (size_t i = 0; i < obstacle->count; i++) {
		if (!(new_x + player->width < (unsigned int)obstacle->instances[i].x || new_x > (unsigned int)obstacle->instances[i].x + 64 ||
			  new_y + player->height < (unsigned int)obstacle->instances[i].y || new_y > (unsigned int)obstacle->instances[i].y + 64)) {
			// New position collides with an obstacle, do not move
			return;
		}
	}
	// Check if the new position collides with any of the collectibles
	for (size_t i = 0; i < collectible->count; i++) {
		if (!(new_x + player->width < (unsigned int)collectible->instances[i].x || new_x > (unsigned int)collectible->instances[i].x + 64 ||
			  new_y + player->height < (unsigned int)collectible->instances[i].y || new_y > (unsigned int)collectible->instances[i].y + 64)) {
			// New position collides with a collectible, remove the collectible
			collectible->instances[i].x = -1;
			collectible->instances[i].y = -1;
            collectibles_taken++; // Increment the number of collectibles taken

			return;
		}
	}

	// Check if the new position collides with the exit
    if (!(new_x + player->width < (unsigned int)sortie->instances[0].x || new_x > (unsigned int)sortie->instances[0].x + 64 ||
          new_y + player->height < (unsigned int)sortie->instances[0].y || new_y > (unsigned int)sortie->instances[0].y + 64)) {
        // New position collides with the exit, check if all collectibles have been taken
        if (collectibles_taken == collectible->count) {
            // All collectibles have been taken, allow the player to exit
            printf("You've collected all collectibles and can now exit!\n");
			mlx_close_window(mlx);
        } else {
            // Not all collectibles have been taken, do not allow the player to exit
            printf("You need to collect all collectibles before you can exit!\n");
            return;
        }
    }
	


	// Check if it is within the window boundaries
	if (new_x >= 0 && new_x <= (unsigned int)mlx->width && new_y >= 0 && new_y <= (unsigned int)mlx->height) {
		player->instances[0].x = new_x;
		player->instances[0].y = new_y;
		if (new_x != old_x || new_y != old_y) {
			total_movements++;
			printf("Total movements: %u\n", total_movements); // Print total movements to the console
		}
	}	
}
