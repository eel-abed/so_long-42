/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:16:45 by eel-abed          #+#    #+#             */
/*   Updated: 2024/06/28 15:58:23 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <libc.h>
# include <MLX42.h>


typedef struct {
    mlx_image_t* player;
    mlx_texture_t* player_texture;
    mlx_texture_t* texture;
    mlx_image_t* obstacle;
    mlx_texture_t* texture_collectible;
    mlx_image_t* collectible;
    mlx_texture_t* texture_sortie;
    mlx_image_t* sortie;
} GameAssets;

typedef	struct s_hook_param
{
	mlx_t		*mlx;
	GameAssets	*game_assets;
}	t_hook_param;



void ft_hook(void* param);
void get_window_dimensions(char *map_name, int *width, int *height);
void read_map(char *map_name, GameAssets *game_assets);
void create_elements(mlx_t *mlx, GameAssets* game_assets);
void display_elements(mlx_t *mlx,mlx_image_t *obstacle, mlx_image_t *collectible);
void ft_error(void);





#endif
