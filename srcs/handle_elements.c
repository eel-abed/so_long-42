/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:40:07 by eel-abed          #+#    #+#             */
/*   Updated: 2024/07/05 14:43:26 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	handle_collectible(unsigned int new_x, unsigned int new_y,
				GameAssets *game_assets)
{
	size_t	i;

	i = 0;
	while (i < game_assets->collectible->count)
	{
		if (!(new_x + game_assets->player->width
				< (unsigned int)game_assets->collectible->instances[i].x
				|| new_x > (unsigned int)game_assets->collectible
				->instances[i].x + 64
				|| new_y + game_assets->player->height
				< (unsigned int)game_assets->collectible->instances[i].y
				|| new_y > (unsigned int)game_assets->collectible
				->instances[i].y + 64))
		{
			game_assets->collectible->instances[i
				+ game_assets->collectible->count].x = 1;
			game_assets->collectible->instances[i].y = 1;
			game_assets->collectibles_taken++;
			return ;
		}
		i++;
	}
}

void	handle_exit(unsigned int new_x, unsigned int new_y,
				GameAssets *game_assets, mlx_t *mlx)
{
	if (!(new_x + game_assets->player->width
			< (unsigned int)game_assets->sortie->instances[0].x
			|| new_x > (unsigned int)game_assets->sortie
			->instances[0].x + 64
			|| new_y + game_assets->player->height
			< (unsigned int)game_assets->sortie->instances[0].y
			|| new_y > (unsigned int)game_assets->sortie
			->instances[0].y + 64))
	{
		if (game_assets->collectibles_taken == game_assets->collectible->count)
		{
			printf("You've collected all collectibles and can now exit!\n");
			mlx_close_window(mlx);
		}
		else
			printf("You need to collect all collectibles before exiting!\n");
	}
}

void	handle_movement(mlx_t *mlx, unsigned int *new_x,
	unsigned int *new_y)
{
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		*new_y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		*new_y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		*new_x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		*new_x += 5;
}
