/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:36:19 by eel-abed          #+#    #+#             */
/*   Updated: 2024/05/12 17:07:40 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"


// Exit the program as failure.
void ft_error(void)
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
	create_elements(mlx);
	// Read the map
	read_map(map_name, player, obstacle, collectible, sortie);
	// Display the elements
	display_elements(mlx,obstacle, collectible);
	mlx_loop_hook(mlx,ft_hook, mlx);
	mlx_loop(mlx);
	

	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}


