/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:40:33 by eel-abed          #+#    #+#             */
/*   Updated: 2024/07/02 19:13:24 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void handle_keys(HookParam *hook_param, unsigned int *new_x, unsigned int *new_y) {
	mlx_t *mlx = hook_param->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		*new_y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		*new_y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		*new_x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		*new_x += 5;
}

bool check_obstacle_collision(GameAssets *game_assets, unsigned int new_x, unsigned int new_y) {
	for (size_t i = 0; i < game_assets->obstacle->count; i++) {
		if (!(new_x + game_assets->player->width < (unsigned int)game_assets->obstacle->instances[i].x || new_x > (unsigned int)game_assets->obstacle->instances[i].x + 64 ||
			  new_y + game_assets->player->height < (unsigned int)game_assets->obstacle->instances[i].y || new_y > (unsigned int)game_assets->obstacle->instances[i].y + 64)) {
			return true;
		}
	}
	return false;
}

void check_collectible_collision(GameAssets *game_assets, unsigned int new_x, unsigned int new_y) {
	for (size_t i = 0; i < game_assets->collectible->count; i++) {
		if (!(new_x + game_assets->player->width < (unsigned int)game_assets->collectible->instances[i].x || new_x > (unsigned int)game_assets->collectible->instances[i].x + 64 ||
			  new_y + game_assets->player->height < (unsigned int)game_assets->collectible->instances[i].y || new_y > (unsigned int)game_assets->collectible->instances[i].y + 64)) {
			game_assets->collectible->instances[i + game_assets->collectible->count].x = 1;
			game_assets->collectible->instances[i].y = 1;
			game_assets->collectibles_taken++;
		}
	}
}

void check_exit_collision(HookParam *hook_param, GameAssets *game_assets, unsigned int new_x, unsigned int new_y) {
	mlx_t *mlx = hook_param->mlx;
	if (!(new_x + game_assets->player->width < (unsigned int)game_assets->sortie->instances[0].x || new_x > (unsigned int)game_assets->sortie->instances[0].x + 64 ||
		  new_y + game_assets->player->height < (unsigned int)game_assets->sortie->instances[0].y || new_y > (unsigned int)game_assets->sortie->instances[0].y + 64)) {
		if (game_assets->collectibles_taken == game_assets->collectible->count) {
			printf("You've collected all collectibles and can now exit!\n");
			mlx_close_window(mlx);
		} else {
			printf("You need to collect all collectibles before you can exit!\n");
		}
	}
}

void ft_hook(void *param) {
	HookParam *hook_param = (HookParam *)param;
	GameAssets *game_assets = hook_param->game_assets;
	mlx_t *mlx = hook_param->mlx;
	unsigned int old_x = game_assets->player->instances[0].x;
	unsigned int old_y = game_assets->player->instances[0].y;
	unsigned int new_x = old_x;
	unsigned int new_y = old_y;

	handle_keys(hook_param, &new_x, &new_y);
	if (check_obstacle_collision(game_assets, new_x, new_y)) return;
	check_collectible_collision(game_assets, new_x, new_y);
	check_exit_collision(hook_param, game_assets, new_x, new_y);
	if (new_x >= 0 && new_x <= (unsigned int)mlx->width && new_y >= 0 && new_y <= (unsigned int)mlx->height)
	{
		game_assets->player->instances[0].x = new_x;
		game_assets->player->instances[0].y = new_y;
		if (new_x != old_x || new_y != old_y)
		{
			game_assets->total_movements++;
			printf("Total movements: %u\n", game_assets->total_movements);
		}
	}
}
