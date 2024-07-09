/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:16:45 by eel-abed          #+#    #+#             */
/*   Updated: 2024/07/09 13:57:49 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <libc.h>
# include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_game_assets
{
	mlx_image_t		*player;
	mlx_texture_t	*player_texture;
	mlx_texture_t	*texture;
	mlx_image_t		*obstacle;
	mlx_texture_t	*texture_collectible;
	mlx_image_t		*collectible;
	mlx_texture_t	*texture_sortie;
	mlx_image_t		*sortie;
	unsigned int	total_movements;
	unsigned int	collectibles_taken;
}	t_game_assets;

typedef struct s_hook_param
{
	mlx_t			*mlx;
	t_game_assets	*game_assets;
}	t_hook_param;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_fill_params
{
	char	**tab;
	t_point	size;
	char	to_fill;
	int		*collectible_count;
	int		*exit_reachable;
}	t_fill_params;

typedef struct s_dimensions
{
	int	max_width;
	int	current_width;
	int	max_height;
	int	first_line_width;
	int	tmp_max_height;
}	t_dimensions;

typedef struct s_game_context
{
	mlx_t			*mlx;
	t_game_assets	game_assets;
	t_dimensions	dim;
	t_hook_param	hook_param;
}	t_game_context;

void	calculate_width(int fd, t_dimensions *dim);
void	calculate_height(int fd, t_dimensions *dim);
int		flood_fill(char **tab, t_point size,
			t_point begin, int collectible_total);
void	ft_hook(void *param);
void	perform_flood_fill(char **map_data, t_dimensions *dim,
			t_game_assets *game_assets);
int		openfile(char *map_name);
void	check_map_validity(t_game_assets *game_assets);
void	get_window_dimensions(char *map_name, int *width,
			int *height, t_dimensions *dim);
void	read_map(char *map_name, t_game_assets *game_assets, t_dimensions *dim);
void	create_elements(mlx_t *mlx, t_game_assets *game_assets);
void	display_elements(mlx_t *mlx, mlx_image_t *obstacle,
			mlx_image_t *collectible);
void	ft_error(void);
void	handle_collectible(unsigned int new_x, unsigned int new_y,
			t_game_assets *game_assets);
void	handle_exit(unsigned int new_x, unsigned int new_y,
			t_game_assets *game_assets, mlx_t *mlx);
void	handle_movement(mlx_t *mlx, unsigned int *new_x, unsigned int *new_y);
void	create_player(mlx_t *mlx, t_game_assets *game_assets);
void	create_obstacle(mlx_t *mlx, t_game_assets *game_assets);
void	create_collectible(mlx_t *mlx, t_game_assets *game_assets);
void	create_sortie(mlx_t *mlx, t_game_assets *game_assets);
void	free_map_data(char **map_data, int max_height);
void	free_elements(mlx_t *mlx, t_game_assets *game_assets);

#endif
