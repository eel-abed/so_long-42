/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:40:33 by eel-abed          #+#    #+#             */
/*   Updated: 2024/07/05 14:43:00 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_collision(unsigned int new_x, unsigned int new_y,
				GameAssets *game_assets)
{
	size_t	i;

	i = 0;
	while (i < game_assets->obstacle->count)
	{
		if (!(new_x + game_assets->player->width
				< (unsigned int)game_assets->obstacle->instances[i].x
				|| new_x > (unsigned int)game_assets->obstacle
				->instances[i].x + 64
				|| new_y + game_assets->player->height
				< (unsigned int)game_assets->obstacle->instances[i].y
				|| new_y > (unsigned int)game_assets->obstacle
				->instances[i].y + 64))
			return (1);
		i++;
	}
	return (0);
}

static void	update_position(GameAssets *game_assets, mlx_t *mlx,
				unsigned int new_x, unsigned int new_y)
{
	unsigned int	old_x;
	unsigned int	old_y;

	old_x = game_assets->player->instances[0].x;
	old_y = game_assets->player->instances[0].y;
	if (new_x >= 0 && new_x <= (unsigned int)mlx->width
		&& new_y >= 0 && new_y <= (unsigned int)mlx->height)
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

void	ft_hook(void *param)
{
	HookParam		*hook_param;
	mlx_t			*mlx;
	GameAssets		*game_assets;
	unsigned int	new_x;
	unsigned int	new_y;

	hook_param = (HookParam *)param;
	mlx = hook_param->mlx;
	game_assets = hook_param->game_assets;
	new_x = game_assets->player->instances[0].x;
	new_y = game_assets->player->instances[0].y;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	handle_movement(mlx, &new_x, &new_y);
	if (check_collision(new_x, new_y, game_assets))
		return ;
	handle_collectible(new_x, new_y, game_assets);
	handle_exit(new_x, new_y, game_assets, mlx);
	update_position(game_assets, mlx, new_x, new_y);
}
