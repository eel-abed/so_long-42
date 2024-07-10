/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:44:52 by eel-abed          #+#    #+#             */
/*   Updated: 2024/07/10 12:51:14 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/so_long.h"

void	create_elements(mlx_t *mlx, t_game_assets *game_assets)
{
	create_obstacle(mlx, game_assets);
	create_collectible(mlx, game_assets);
	create_sortie(mlx, game_assets);
	create_player(mlx, game_assets);
}

void	create_player(mlx_t *mlx, t_game_assets *game_assets)
{
	game_assets->player_texture = mlx_load_png("assets/player.png");
	game_assets->player = mlx_texture_to_image(mlx,
			game_assets->player_texture);
	game_assets->player->instances = malloc
		(sizeof(*game_assets->player->instances));
	if (mlx_image_to_window(mlx, game_assets->player,
			game_assets->player->instances[0].x,
			game_assets->player->instances[0].y) < 0)
		ft_error();
}

void	create_obstacle(mlx_t *mlx, t_game_assets *game_assets)
{
	game_assets->texture = mlx_load_png("assets/mur.png");
	game_assets->obstacle = mlx_texture_to_image(mlx, game_assets->texture);
	game_assets->obstacle->instances = malloc(999
			* sizeof(*game_assets->obstacle->instances));
}

void	create_collectible(mlx_t *mlx, t_game_assets *game_assets)
{
	game_assets->texture_collectible = mlx_load_png("assets/fish.png");
	game_assets->collectible = mlx_texture_to_image(mlx,
			game_assets->texture_collectible);
	game_assets->collectible->instances = malloc(999
			* sizeof(*game_assets->collectible->instances));
}

void	create_sortie(mlx_t *mlx, t_game_assets *game_assets)
{
	game_assets->texture_sortie = mlx_load_png("assets/sortie.png");
	game_assets->sortie = mlx_texture_to_image(mlx,
			game_assets->texture_sortie);
	game_assets->sortie->instances = malloc
		(sizeof(*game_assets->sortie->instances));
	if (mlx_image_to_window(mlx, game_assets->sortie,
			game_assets->sortie->instances[0].x,
			game_assets->sortie->instances[0].y) < 0)
		ft_error();
}
