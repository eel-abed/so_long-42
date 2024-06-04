/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:44:52 by eel-abed          #+#    #+#             */
/*   Updated: 2024/06/04 15:47:06 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	create_elements(mlx_t *mlx)
{
	player_texture = mlx_load_png("assets/player.png");
	player = mlx_texture_to_image(mlx, player_texture);
	player->instances = malloc(sizeof(*player->instances));
	if (mlx_image_to_window(mlx, player,
			player->instances[0].x, player->instances[0].y) < 0)
	{
		ft_error();
	}
	texture = mlx_load_png("assets/mur.png");
	obstacle = mlx_texture_to_image(mlx, texture);
	obstacle->instances = malloc(sizeof(*obstacle->instances));
	texture_collectible = mlx_load_png("assets/fish.png");
	collectible = mlx_texture_to_image(mlx, texture_collectible);
	collectible->instances = malloc(sizeof(*collectible->instances));
	texture_sortie = mlx_load_png("assets/sortie.png");
	sortie = mlx_texture_to_image(mlx, texture_sortie);
	sortie->instances = malloc(sizeof(*sortie->instances));
	if (mlx_image_to_window(mlx, sortie,
			sortie->instances[0].x, sortie->instances[0].y) < 0)
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
