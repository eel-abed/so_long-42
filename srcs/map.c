/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:39:07 by eel-abed          #+#    #+#             */
/*   Updated: 2024/07/02 17:38:09 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_window_dimensions(char *map_name,
	int *width, int *height, Dimensions *dim)
{
	int	fd;

	fd = open(map_name, O_RDONLY);
	if (fd == -1)
	{
		printf("Could not open file %s\n", map_name);
		return ;
	}
	calculate_height(fd, dim);
	close(fd);
	fd = open(map_name, O_RDONLY);
	calculate_width(fd, dim);
	*width = dim->max_width * 64;
	*height = dim->max_height * 64;
	close(fd);
}

void	process_char_instances(char ch, int x, int y, GameAssets *game_assets)
{
	if (ch == '1')
	{
		game_assets->obstacle->instances[game_assets->obstacle->count].x
			= x * 64;
		game_assets->obstacle->instances[game_assets->obstacle->count].y
			= y * 64;
		game_assets->obstacle->count++;
	}
	else if (ch == 'C')
	{
		game_assets->collectible->instances[game_assets->collectible->count].x
			= x * 64;
		game_assets->collectible->instances[game_assets->collectible->count].y
			= y * 64;
		game_assets->collectible->count++;
	}
}

void	process_char_no_inst(char ch, int x, int y, GameAssets *game_assets)
{
	if (ch == 'P')
	{
		game_assets->player->instances[0].x = x * 64;
		game_assets->player->instances[0].y = y * 64;
		game_assets->player->count++;
	}
	else if (ch == 'E')
	{
		game_assets->sortie->instances[0].x = x * 64;
		game_assets->sortie->instances[0].y = y * 64;
		game_assets->sortie->count++;
	}
}

void	check_map_validity(GameAssets *game_assets)
{
	if (game_assets->player->count != 1)
	{
		printf("Error: Map must contain exactly one player start position.\n");
		ft_error();
	}
	if (game_assets->sortie->count != 1)
	{
		printf("Error: Map must contain exactly one exit.\n");
		ft_error();
	}
	if (game_assets->collectible->count < 1)
	{
		printf("Error: Map must contain at least one collectible.\n");
		ft_error();
	}
}

void	read_map(char *map_name, GameAssets *game_assets, Dimensions *dim)
{
	int fd = open(map_name, O_RDONLY);
	if (fd == -1) { printf("Could not open file %s\n", map_name); return; }
	char ch, **map_data = malloc(dim->max_height * sizeof(char *));
	for (int i = 0; i < dim->max_height; i++) map_data[i] = malloc(128 * sizeof(char));
	int x = 0, y = 0, row = 0, col = 0;
	game_assets->player->count = game_assets->obstacle->count = game_assets->collectible->count = game_assets->sortie->count = 0;
	while (read(fd, &ch, 1) > 0) {
		if (ch == '\n') { map_data[row][col] = '\0'; row++; col = 0; y++; x = 0; }
		else {
			map_data[row][col++] = ch;
			process_char_instances(ch, x, y, game_assets);
			process_char_no_inst(ch, x, y, game_assets);
			x++;
		}
	}
	close(fd);
	check_map_validity(game_assets);
	perform_flood_fill(map_data, dim, game_assets);
	for (int i = 0; i < dim->max_height; i++) free(map_data[i]);
	free(map_data);
}
