/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_elem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:13:12 by eel-abed          #+#    #+#             */
/*   Updated: 2024/07/09 15:24:32 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/so_long.h"

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
