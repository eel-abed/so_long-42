/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:36:19 by eel-abed          #+#    #+#             */
/*   Updated: 2024/07/09 13:32:22 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_error(void)
{
	printf("ERROR\n");
	exit(EXIT_FAILURE);
}

void	get_window_dimensions(char *map_name,
	int *width, int *height, Dimensions *dim)
{
	int	fd;

	fd = openfile(map_name);
	calculate_height(fd, dim);
	close(fd);
	fd = open(map_name, O_RDONLY);
	calculate_width(fd, dim);
	*width = dim->max_width * 64;
	*height = dim->max_height * 64;
	if ((*width > 2500) || (*height > 1000))
	{
		printf("Error: Map size is too big.\n");
		close(fd);
		ft_error();
	}
	close(fd);
}

static void	init_game_assets(mlx_t *mlx, GameAssets *game_assets
	, char *map_name, Dimensions *dim)
{
	game_assets->total_movements = 0;
	game_assets->collectibles_taken = 0;
	create_elements(mlx, game_assets);
	read_map(map_name, game_assets, dim);
	display_elements(mlx, game_assets->obstacle, game_assets->collectible);
}

int	main(int argc, char **argv)
{
	t_game_context	game;

	game.dim = (Dimensions){0, 0, 0, -1, 0};
	if (argc < 2)
	{
		printf("Usage: %s <map_name>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	get_window_dimensions(argv[1], &game.dim.max_width,
		&game.dim.max_height, &game.dim);
	game.mlx = mlx_init(game.dim.max_width, game.dim.max_height, "Test", false);
	if (!game.mlx)
		ft_error();
	init_game_assets(game.mlx, &game.game_assets, argv[1], &game.dim);
	game.hook_param.mlx = game.mlx;
	game.hook_param.game_assets = &game.game_assets;
	mlx_loop_hook(game.mlx, ft_hook, &game.hook_param);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	free_elements(game.mlx, &game.game_assets);
	return (EXIT_SUCCESS);
}
