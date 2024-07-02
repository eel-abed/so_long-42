/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:36:19 by eel-abed          #+#    #+#             */
/*   Updated: 2024/07/02 19:03:55 by eel-abed         ###   ########.fr       */
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

	fd = openFile(map_name);
	calculate_height(fd, dim);
	close(fd);
	fd = open(map_name, O_RDONLY);
	calculate_width(fd, dim);
	*width = dim->max_width * 64;
	*height = dim->max_height * 64;
	close(fd);
}

static void	init_game_assets(mlx_t *mlx, GameAssets *game_assets
	, char *map_name, Dimensions *dim)
{
	game_assets->total_movements = 0;
	game_assets->collectibles_taken = 0;
	game_assets->player = malloc(sizeof(mlx_image_t));
	create_elements(mlx, game_assets);
	read_map(map_name, game_assets, dim);
	display_elements(mlx, game_assets->obstacle, game_assets->collectible);
}

int	main(int argc, char **argv)
{
	t_hook_param	hook_param;
	int				width;
	int				height;
	mlx_t			*mlx;
	GameAssets		game_assets;

	if (argc < 2)
	{
		printf("Usage: %s <map_name>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	Dimensions dim = {0, 0, 0, -1, 0};
	get_window_dimensions(argv[1], &width, &height, &dim);
	mlx = mlx_init(width, height, "Test", false);
	if (!mlx)
		ft_error();
	init_game_assets(mlx, &game_assets, argv[1], &dim);
	hook_param.mlx = mlx;
	hook_param.game_assets = &game_assets;
	mlx_loop_hook(mlx, ft_hook, &hook_param);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
