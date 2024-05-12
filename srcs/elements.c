/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:44:52 by eel-abed          #+#    #+#             */
/*   Updated: 2024/05/12 17:11:56 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"


void create_elements(mlx_t *mlx)
{
	// Create a player
	player = mlx_new_image(mlx, 30, 30);
	if (!player)
		ft_error();

	// Set every pixel to white
	memset(player->pixels, 255, player->width * player->height * sizeof(int32_t));

	// Allocate space for the player instance
	player->instances = malloc(sizeof(*player->instances));
	if (!player->instances)
		ft_error();

	// Display an instance of the player
	if (mlx_image_to_window(mlx, player, player->instances[0].x, player->instances[0].y) < 0)
		ft_error();
		

	// Create a obstacle
	obstacle = mlx_new_image(mlx, 64, 64);
	if (!obstacle)
		ft_error();
	
	// Allocate space for the obstacle instances
	obstacle->instances = malloc(sizeof(*obstacle->instances));

	// Set every pixel to black
	memset(obstacle->pixels, 222, obstacle->width * obstacle->height * sizeof(int32_t));

	// Create a collectible
	collectible = mlx_new_image(mlx, 64, 64);
	if (!collectible)
		ft_error();
	
	// Allocate space for the collectible instances
	collectible->instances = malloc(sizeof(*collectible->instances));
	if (!collectible->instances)
		ft_error();

	// Set every pixel to yellow
	memset(collectible->pixels, 111, collectible->width * collectible->height * sizeof(int32_t));
	
	// Create a sortie
	sortie = mlx_new_image(mlx, 64, 64);
	if (!sortie)
		ft_error();
	
	// Allocate space for the sortie instances
	sortie->instances = malloc(sizeof(*sortie->instances));
	if (!sortie->instances)
		ft_error();
	// Set every pixel 
	memset(sortie->pixels, 445, sortie->width * sortie->height * sizeof(int32_t));

	//Display an instance of the sortie
	if (mlx_image_to_window(mlx, sortie, sortie->instances[0].x, sortie->instances[0].y) < 0)
		ft_error();
}

void display_elements(mlx_t *mlx, mlx_image_t *obstacle, mlx_image_t *collectible)
{
	//Display collectible
	int o = collectible->count;
	int g = 0;
	while(o != 0)
	{
		mlx_image_to_window(mlx, collectible, collectible->instances[g].x, collectible->instances[g].y);
		o--;
		g++;
	}

	int a = obstacle->count;
	int f = 0;
	while(a != 0)
	{
		mlx_image_to_window(mlx, obstacle, obstacle->instances[f].x, obstacle->instances[f].y);
		a--;
		f++;
	}
}
