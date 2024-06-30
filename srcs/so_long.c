/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:36:19 by eel-abed          #+#    #+#             */
/*   Updated: 2024/06/30 13:17:40 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_error(void)
{
	printf("ERROR\n");
	exit(EXIT_FAILURE);
}

static void	init_game_assets(mlx_t *mlx, GameAssets *game_assets
	, char *map_name, Dimensions *dim)
{
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
