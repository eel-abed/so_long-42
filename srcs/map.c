/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:39:07 by eel-abed          #+#    #+#             */
/*   Updated: 2024/06/27 18:26:13 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"


void get_window_dimensions(char *map_name, int *width, int *height)
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
	//get max_height temporary
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
		//chekc the last row if it's 1
		if (tmp_max_height -1 == max_height && ch != '1' && ch != '\n')
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

void read_map(char *map_name, mlx_image_t *player, mlx_image_t *obstacle, mlx_image_t *collectible, mlx_image_t *sortie)
{
	FILE *file = fopen(map_name, "r");
	if (file == NULL)
	{
		printf("Could not open file %s\n", map_name);
		return;
	}

	char ch;
	int x = 0, y = 0;

	while ((ch = fgetc(file)) != EOF)
	{
		if (ch == '\n')
		{
			x = 0;
			y++;
		}
		else
		{
			if (ch == '1')
			{
				// Create an obstacle at (x, y)
				obstacle->instances = realloc(obstacle->instances, (obstacle->count + 1) * sizeof(*obstacle->instances));
				obstacle->instances[obstacle->count].x = x * 64;
				obstacle->instances[obstacle->count].y = y * 64;
				obstacle->count++;
			}
			else if (ch == 'P')
			{
				// Set the player's starting position
				player->instances = realloc(player->instances, sizeof(*player->instances));
				player->instances[0].x = x * 64 + 5;
				player->instances[0].y = y * 64 + 5;
				player->count++;
			}
			else if (ch == 'C')
			{
				collectible->instances = realloc(collectible->instances, (collectible->count + 1) * sizeof(*collectible->instances));
				collectible->instances[collectible->count].x = x * 64;
				collectible->instances[collectible->count].y = y * 64;
				collectible->count++;
			}
			else if (ch == 'E')
			{
				sortie->instances = realloc(sortie->instances, sizeof(*sortie->instances));
				sortie->instances[0].x = x * 64;
				sortie->instances[0].y = y * 64;
				sortie->count++;	
			}
			

			x++;
		}
	}

	fclose(file);
    // Check for map validity
    if (player->count != 2)
    {
        printf("Error: Map must contain exactly one player start position.\n");
        ft_error();
    }
    if (sortie->count != 2)
    {
        printf("Error: Map must contain exactly one exit.\n");
        ft_error();
    }
    if (collectible->count < 1)
    {
        printf("Error: Map must contain at least one collectible.\n");
        ft_error();
    }
}

