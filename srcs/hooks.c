/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:40:33 by eel-abed          #+#    #+#             */
/*   Updated: 2024/06/28 15:45:13 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"


unsigned int total_movements = 0; // Global variable to keep track of total movements
unsigned int collectibles_taken = 0; // Global variable to keep track of collectibles taken
typedef struct HookParam {
    mlx_t* mlx;
    GameAssets* game_assets;
} HookParam;
void ft_hook(void* param)
{
	HookParam* hook_param = (HookParam*)param;
    mlx_t* mlx = hook_param->mlx;
    GameAssets* game_assets = hook_param->game_assets;
	
	unsigned int old_x = game_assets->player->instances[0].x;
	unsigned int old_y = game_assets->player->instances[0].y;
	

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
	for (size_t i = 0; i < game_assets->obstacle->count; i++) {
		if (!(new_x + game_assets->player->width < (unsigned int)game_assets->obstacle->instances[i].x || new_x > (unsigned int)game_assets->obstacle->instances[i].x + 64 ||
			  new_y + game_assets->player->height < (unsigned int)game_assets->obstacle->instances[i].y || new_y > (unsigned int)game_assets->obstacle->instances[i].y + 64)) {
			// New position collides with an obstacle, do not move
			return;
		}
	}
	// Check if the new position collides with any of the collectibles
	for (size_t i = 0; i < game_assets->collectible->count; i++) {
		if (!(new_x + game_assets->player->width < (unsigned int)game_assets->collectible->instances[i].x || new_x > (unsigned int)game_assets->collectible->instances[i].x + 64 ||
			  new_y + game_assets->player->height < (unsigned int)game_assets->collectible->instances[i].y || new_y > (unsigned int)game_assets->collectible->instances[i].y + 64)) {
			// New position collides with a collectible, remove the collectible
			game_assets->collectible->instances[i + game_assets->collectible->count].x = 1;
			game_assets->collectible->instances[i].y = 1;
			collectibles_taken++; // Increment the number of collectibles taken

			return;
		}
	}

	// Check if the new position collides with the exit
	if (!(new_x + game_assets->player->width < (unsigned int)game_assets->sortie->instances[0].x || new_x > (unsigned int)game_assets->sortie->instances[0].x + 64 ||
		  new_y + game_assets->player->height < (unsigned int)game_assets->sortie->instances[0].y || new_y > (unsigned int)game_assets->sortie->instances[0].y + 64)) {
		// New position collides with the exit, check if all collectibles have been taken
		if (collectibles_taken == game_assets->collectible->count) {
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
		game_assets->player->instances[0].x = new_x;
		game_assets->player->instances[0].y = new_y;
		if (new_x != old_x || new_y != old_y) {
			total_movements++;
			printf("Total movements: %u\n", total_movements); // Print total movements to the console
		}
	}
}
