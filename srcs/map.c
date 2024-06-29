/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:39:07 by eel-abed          #+#    #+#             */
/*   Updated: 2024/06/29 17:11:44 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"






//error function when map not surrounded by walls
void ft_map_wall_error()
{
	printf("Error: Map must be surrounded by walls.\n");
	ft_error();
}

void get_window_dimensions(char *map_name, int *width, int *height)
{
	int fd;
	char ch;
	Dimensions dim = {0, 0, 0, -1, 0};

	fd = open(map_name, O_RDONLY);
	if (fd == -1)
	{
		printf("Could not open file %s\n", map_name);
		return;
	}
	//caluclate height
	while (read(fd, &ch, 1) > 0)
	{
		if (ch == '\n')
		{
			dim.tmp_max_height++;
		}
	}
	close(fd);
	fd = open(map_name, O_RDONLY);
	while (read(fd, &ch, 1) > 0)
	{
		if ((dim.current_width == 0 || dim.current_width == dim.max_width) && ch != '1' && ch != '\n')
		{
			close(fd);
			ft_map_wall_error();
		}
		if (ch == '\n')
		{
			if (dim.first_line_width == -1)
				dim.first_line_width = dim.current_width;
			else if (dim.current_width != dim.first_line_width)
			{
				printf("Error: Map must be rectangular.\n");
				close(fd);
				ft_error();
				return;
			}
			if (dim.current_width > dim.max_width)
				dim.max_width = dim.current_width;
			dim.current_width = 0;
			dim.max_height++;
		}
		else
		{
			dim.current_width++;
		}
		if (dim.first_line_width == -1 && ch != '1')
		{
			close(fd);
			ft_map_wall_error();
		}
		if (dim.max_height == dim.tmp_max_height - 1)
		{
			if (ch != '1' && ch != '\n')
			{
				close(fd);
				ft_map_wall_error();
			}
		}
	}

	*width = dim.max_width * 64;
	*height = dim.max_height * 64;

	close(fd);
}

void read_map(char *map_name, GameAssets* game_assets)
{
	mlx_image_t *player = game_assets->player;
	mlx_image_t *obstacle = game_assets->obstacle;
	mlx_image_t *collectible = game_assets->collectible;
	mlx_image_t *sortie = game_assets->sortie;
	FILE *file = fopen(map_name, "r");
	if (file == NULL)
	{
		printf("Could not open file %s\n", map_name);
		return;
	}
	char ch;
	int x = 0, y = 0;
	int player_start_x = -1, player_start_y = -1;
	int collectible_total = 0;
	game_assets->player->count = 0;
	game_assets->obstacle->count = 0;
	game_assets->collectible->count = 0;
	game_assets->sortie->count = 0;
	char **map_data = NULL;
	int map_height = 0;
	while ((ch = fgetc(file)) != EOF)
	{
		if (ch == '\n')
		{
			map_height++;
		}
	}
	rewind(file);
	map_data = (char **)malloc(map_height * sizeof(char *));
	for (int i = 0; i < map_height; i++)
	{
		map_data[i] = (char *)malloc(128 * sizeof(char));
	}
	int row = 0, col = 0;
	while ((ch = fgetc(file)) != EOF)
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
			map_data[row][col] = ch;
			if (ch == '1')
			{
				obstacle->instances = realloc(obstacle->instances, (obstacle->count + 1) * sizeof(*obstacle->instances));
				obstacle->instances[obstacle->count].x = x * 64;
				obstacle->instances[obstacle->count].y = y * 64;
				obstacle->count++;
			}
			else if (ch == 'P')
			{
				player->instances = realloc(player->instances, sizeof(*player->instances));
				player->instances[0].x = x * 64 + 5;
				player->instances[0].y = y * 64 + 5;
				player->count++;
				player_start_x = x;
				player_start_y = y;
			}
			else if (ch == 'C')
			{
				collectible->instances = realloc(collectible->instances, (collectible->count + 1) * sizeof(*collectible->instances));
				collectible->instances[collectible->count].x = x * 64;
				collectible->instances[collectible->count].y = y * 64;
				collectible->count++;
				collectible_total++;
			}
			else if (ch == 'E')
			{
				sortie->instances = realloc(sortie->instances, sizeof(*sortie->instances));
				sortie->instances[0].x = x * 64;
				sortie->instances[0].y = y * 64;
				sortie->count++;
			}
			col++;
			x++;
		}
	}
	fclose(file);
	if (player->count != 1)
	{
		printf("Error: Map must contain exactly one player start position.\n");
		ft_error();
	}
	if (sortie->count != 1)
	{
		printf("Error: Map must contain exactly one exit.\n");
		ft_error();
	}
	if (collectible->count < 1)
	{
		printf("Error: Map must contain at least one collectible.\n");
		ft_error();
	}
	t_point size = {128, map_height};
	t_point start = {player_start_x, player_start_y};
	if (!flood_fill(map_data, size, start, collectible_total))
	{
		printf("Error: Player cannot reach the exit or collect all collectibles.\n");
		ft_error();
	}
	for (int i = 0; i < map_height; i++)
	{
		free(map_data[i]);
	}
	free(map_data);
}
