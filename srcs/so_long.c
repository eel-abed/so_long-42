/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:36:19 by eel-abed          #+#    #+#             */
/*   Updated: 2024/05/12 15:44:15 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"


// Exit the program as failure.
static void ft_error(void)
{
    fprintf(stderr, "%s", mlx_strerror(mlx_errno));
    exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("Usage: %s <map_name>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	char *map_name = argv[1];
	int width, height;
	get_window_dimensions(map_name, &width, &height);
	
	// Start mlx
	mlx_t* mlx = mlx_init(width,height, "Test", false);
	if (!mlx)
        ft_error();

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

	// Set every pixel to black
	memset(obstacle->pixels, 222, obstacle->width * obstacle->height * sizeof(int32_t));

	// Create a collectible
	collectible = mlx_new_image(mlx, 64, 64);
	if (!collectible)
		ft_error();
	
	// Allocate space for the collectible instances
	collectible->instances = malloc(sizeof(*collectible->instances));


	// Set every pixel to yellow
	memset(collectible->pixels, 333, collectible->width * collectible->height * sizeof(int32_t));



	// Create a sortie
	sortie = mlx_new_image(mlx, 64, 64);
	if (!sortie)
		ft_error();

	// Allocate space for the sortie instances
	sortie->instances = malloc(sizeof(*sortie->instances));

	// Set every pixel to green
	memset(sortie->pixels, 444, sortie->width * sortie->height * sizeof(int32_t));


	//Display sortie
	if (mlx_image_to_window(mlx, sortie, sortie->instances[0].x, sortie->instances[0].y) < 0)
		ft_error();

    read_map(map_name, player, obstacle, collectible, sortie);

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


	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	

	// Optional, terminate will clean up any leftovers, this is just to demonstrate.
	mlx_delete_image(mlx, player);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}


