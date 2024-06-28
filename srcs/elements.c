/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:44:52 by eel-abed          #+#    #+#             */
/*   Updated: 2024/06/28 15:00:54 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	create_elements(mlx_t *mlx, GameAssets* game_assets)
{
	// Player
	game_assets->player_texture = mlx_load_png("assets/player.png");
	game_assets->player = mlx_texture_to_image(mlx, game_assets->player_texture);
	game_assets->player->instances = malloc(sizeof(*game_assets->player->instances));

	if (mlx_image_to_window(mlx, game_assets->player,
			game_assets->player->instances[0].x, game_assets->player->instances[0].y) < 0)
	{
		ft_error();
	}

	// Obstacle
	game_assets->obstacle = malloc(sizeof(mlx_image_t));
	game_assets->texture = mlx_load_png("assets/mur.png");
	game_assets->obstacle = mlx_texture_to_image(mlx, game_assets->texture);
	game_assets->obstacle->instances = malloc(sizeof(*game_assets->obstacle->instances));

	// Collectible
	game_assets->collectible = malloc(sizeof(mlx_image_t));
	game_assets->texture_collectible = mlx_load_png("assets/fish.png");
	game_assets->collectible = mlx_texture_to_image(mlx, game_assets->texture_collectible);
	game_assets->collectible->instances = malloc(sizeof(*game_assets->collectible->instances));

	// Sortie
	game_assets->sortie = malloc(sizeof(mlx_image_t));
	game_assets->texture_sortie = mlx_load_png("assets/sortie.png");
	game_assets->sortie = mlx_texture_to_image(mlx, game_assets->texture_sortie);
	game_assets->sortie->instances = malloc(sizeof(*game_assets->sortie->instances));

	if (mlx_image_to_window(mlx, game_assets->sortie,
			game_assets->sortie->instances[0].x, game_assets->sortie->instances[0].y) < 0)
	{
		ft_error();
	}
}
void	display_collectibles(mlx_t *mlx, mlx_image_t *collectible)
{
	int	original_count;
	int	o;
	int	g;

	original_count = collectible->count;
	o = collectible->count;
	g = 0;
	while (o != 0)
	{
		mlx_image_to_window(mlx, collectible,
			collectible->instances[g].x + 16, collectible->instances[g].y + 16);
		o--;
		g++;
	}
	collectible->count = original_count;
}

void	display_obstacles(mlx_t *mlx, mlx_image_t *obstacle)
{
	int	a;
	int	f;

	a = obstacle->count;
	f = 0;
	while (a != 0)
	{
		mlx_image_to_window(mlx, obstacle,
			obstacle->instances[f].x, obstacle->instances[f].y);
		a--;
		f++;
	}
}

void	display_elements(mlx_t *mlx, mlx_image_t *obstacle,
	mlx_image_t *collectible)
{
	display_collectibles(mlx, collectible);
	display_obstacles(mlx, obstacle);
}
