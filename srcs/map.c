/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:39:07 by eel-abed          #+#    #+#             */
/*   Updated: 2024/06/27 20:43:09 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"

typedef struct s_point
{
    int x;
    int y;
} t_point;


void fill(char **tab, t_point size, t_point cur, char to_fill, int *collectible_count, int *exit_reachable)
{
    if (cur.y < 0 || cur.y >= size.y || cur.x < 0 || cur.x >= size.x || tab[cur.y][cur.x] == '1' || tab[cur.y][cur.x] == 'F')
        return;

    if (tab[cur.y][cur.x] == 'C')
        (*collectible_count)++;
    if (tab[cur.y][cur.x] == 'E')
        *exit_reachable = 1;

    tab[cur.y][cur.x] = 'F'; // Marquer comme visité

    fill(tab, size, (t_point){cur.x - 1, cur.y}, to_fill, collectible_count, exit_reachable);
    fill(tab, size, (t_point){cur.x + 1, cur.y}, to_fill, collectible_count, exit_reachable);
    fill(tab, size, (t_point){cur.x, cur.y - 1}, to_fill, collectible_count, exit_reachable);
    fill(tab, size, (t_point){cur.x, cur.y + 1}, to_fill, collectible_count, exit_reachable);
}

int flood_fill(char **tab, t_point size, t_point begin, int collectible_total)
{
    int collectible_count = 0;
    int exit_reachable = 0;

    fill(tab, size, begin, tab[begin.y][begin.x], &collectible_count, &exit_reachable);

    return (collectible_count == collectible_total && exit_reachable);
}

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

    // get max_height temporary
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
        // check the last row if it's 1
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
    int player_start_x = -1, player_start_y = -1;
    int collectible_total = 0;
	player->count = 0;
	obstacle->count = 0;
	collectible->count = 0;
	sortie->count = 0;
    char **map_data = NULL;
    int map_height = 0;

    // First pass to get the dimensions
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\n')
        {
            map_height++;
        }
    }
    rewind(file);

    // Allocate memory for map data
    map_data = (char **)malloc(map_height * sizeof(char *));
    for (int i = 0; i < map_height; i++)
    {
        map_data[i] = (char *)malloc(128 * sizeof(char)); // assuming max width is 128
    }

    // Second pass to read the map
    int row = 0, col = 0;
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\n')
        {
            map_data[row][col] = '\0'; // null-terminate the string
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

    // Check for map validity
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

    // Validate the map using flood fill
    t_point size = {128, map_height}; // assuming max width is 128
    t_point start = {player_start_x, player_start_y};

    if (!flood_fill(map_data, size, start, collectible_total))
    {
        printf("Error: Player cannot reach the exit or collect all collectibles.\n");
        ft_error();
    }

    // Free allocated memory for map data
    for (int i = 0; i < map_height; i++)
    {
        free(map_data[i]);
    }
    free(map_data);
}
