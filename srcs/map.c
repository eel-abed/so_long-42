/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:39:07 by eel-abed          #+#    #+#             */
/*   Updated: 2024/07/09 13:56:31 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	process_char_instances(char ch, int x, int y,
	t_game_assets *game_assets)
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

void	process_char_no_inst(char ch, int x, int y, t_game_assets *game_assets)
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

void	initialize(int *row, int *col, int *x, int *y)
{
	*row = 0;
	*col = 0;
	*x = 0;
	*y = 0;
}

void	ini_map( char **map_data, t_game_assets *game_assets, int fd)
{
	char	ch;
	int		x;
	int		y;
	int		row;
	int		col;

	initialize(&row, &col, &x, &y);
	while (read(fd, &ch, 1) > 0)
	{
		if (ch == '\n')
		{
			map_data[row][col] = '\0';
			row++;
			col = 0;
			y++;
			x = 0;
		}
		else
		{
			map_data[row][col++] = ch;
			process_char_instances(ch, x, y, game_assets);
			process_char_no_inst(ch, x, y, game_assets);
			x++;
		}
	}
}

void	read_map(char *map_name, t_game_assets *game_assets, t_dimensions *dim)
{
	int		fd ;
	char	**map_data;
	int		i;

	i = 0;
	map_data = malloc(dim->max_height * sizeof(char *));
	while (i < dim->max_height)
	{
		map_data[i] = malloc(128 * sizeof(char));
		i++;
	}
	game_assets->player->count = 0;
	game_assets->obstacle->count = 0;
	game_assets->collectible->count = 0;
	game_assets->sortie->count = 0;
	fd = openfile(map_name);
	ini_map(map_data, game_assets, fd);
	close(fd);
	check_map_validity(game_assets);
	perform_flood_fill(map_data, dim, game_assets);
	free_map_data(map_data, dim->max_height);
}
