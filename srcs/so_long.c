/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:36:19 by eel-abed          #+#    #+#             */
/*   Updated: 2024/04/16 18:39:28 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"


int main(void)
{
	mlx_t *mlx;
	int width = 800;
	int height = 600;
	const char *title = "so_long";
	bool resize = false;

	mlx = mlx_init(width, height, title, resize);
	if (!mlx)
	{
		// Handle error
		return 1;
	}

	// TODO: Add your game loop here

	// Clean up
	// TODO: Add your cleanup code here

	return 0;
}
