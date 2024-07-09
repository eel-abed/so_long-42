/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:31:09 by eel-abed          #+#    #+#             */
/*   Updated: 2024/07/09 13:54:12 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map_data(char **map_data, int max_height)
{
	int	i;

	i = 0;
	while (i < max_height)
	{
		free(map_data[i]);
		i++;
	}
	free(map_data);
}

void	free_elements(mlx_t *mlx, t_game_assets *game_assets)
{
	mlx_delete_image(mlx, game_assets->player);
	mlx_delete_image(mlx, game_assets->obstacle);
	mlx_delete_image(mlx, game_assets->collectible);
	mlx_delete_image(mlx, game_assets->sortie);
	mlx_delete_texture(game_assets->player_texture);
	mlx_delete_texture(game_assets->texture);
	mlx_delete_texture(game_assets->texture_collectible);
	mlx_delete_texture(game_assets->texture_sortie);
}
