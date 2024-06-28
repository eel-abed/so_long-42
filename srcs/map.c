/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:39:07 by eel-abed          #+#    #+#             */
/*   Updated: 2024/06/28 17:15:55 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	fill(t_point cur, t_fill_params *params)
{
	if (cur.y < 0)
		return ;
	if (cur.y >= params->size.y)
		return ;
	if (cur.x < 0)
		return ;
	if (cur.x >= params->size.x)
		return ;
	if (params->tab[cur.y][cur.x] == '1')
		return ;
	if (params->tab[cur.y][cur.x] == 'F')
		return ;
	if (params->tab[cur.y][cur.x] == 'C')
		(*params->collectible_count)++;
	if (params->tab[cur.y][cur.x] == 'E')
		*params->exit_reachable = 1;
	params->tab[cur.y][cur.x] = 'F';
	fill((t_point){cur.x - 1, cur.y}, params);
	fill((t_point){cur.x + 1, cur.y}, params);
	fill((t_point){cur.x, cur.y - 1}, params);
	fill((t_point){cur.x, cur.y + 1}, params);
}

int	flood_fill(char **tab, t_point size, t_point begin, int collectible_total)
{
	int				collectible_count;
	int				exit_reachable;
	t_fill_params	params;

	params.tab = tab;
	params.size = size;
	params.to_fill = tab[begin.y][begin.x];
	params.collectible_count = &collectible_count;
	params.exit_reachable = &exit_reachable;
	collectible_count = 0;
	exit_reachable = 0;
	fill(begin, &params);
	return (collectible_count == collectible_total && exit_reachable);
}

void	get_window_dimensions(char *map_name, int *width, int *height)
{
	FILE *file = fopen(map_name, "r");
	if (file == NULL)
	{
		printf("Could not open file %s\n", map_name);
		return;
	}
	char ch;
	int max_width = 0, current_width = 0, max_height = 0;
	int first_line_width = -1;
	int tmp_max_height = 0;
	while ((ch = fgetc(file)) != EOF)
	{
		if (ch == '\n')
		{
			tmp_max_height++;
		}
	}
	rewind(file);
	while ((ch = fgetc(file)) != EOF)
	{
		if ((current_width == 0 || current_width == max_width) && ch != '1' && ch != '\n')
		{
			printf("Error: Map must be surrounded by walls.\n");
			fclose(file);
			ft_error();
		}
		if (ch == '\n')
		{
			if (first_line_width == -1)
				first_line_width = current_width;
			else if (current_width != first_line_width)
			{
				printf("Error: Map must be rectangular.\n");
				fclose(file);
				ft_error();
			}
			if (current_width > max_width)
				max_width = current_width;
			current_width = 0;
			max_height++;
		}
		else
		{
			current_width++;
		}
		if (first_line_width == -1 && ch != '1')
		{
			printf("Error: Map must be surrounded by walls.\n");
			fclose(file);
			ft_error();
		}
		if ((current_width == 0 || current_width == max_width) && ch != '1' && ch != '\n')
		{
			printf("Error: Map must be surrounded by walls.\n");
			fclose(file);
			ft_error();
		}
		if (tmp_max_height - 1 == max_height && ch != '1' && ch != '\n')
		{
			printf("Error: Map must be surrounded by walls.\n");
			fclose(file);
			ft_error();
		}
	}
	*width = max_width * 64;
	*height = max_height * 64;
	fclose(file);
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
