/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:36:19 by eel-abed          #+#    #+#             */
/*   Updated: 2024/04/30 21:44:42 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "so_long.h"

#define MAP_WIDTH 10
#define MAP_HEIGHT 10
#define TILE_SIZE 50

// Define the structure for the game
typedef struct s_game
{
    mlx_t *mlx;
    int map[MAP_WIDTH][MAP_HEIGHT];
    int player_x;
    int player_y;
    int score;
} t_game;

// Function to load the map from .ber file
void load_map(t_game *game, char *file_name)
{
    int fd = open(file_name, O_RDONLY);
    if (fd == -1)
    {
        fprintf(stderr, "Error opening file: %s\n", file_name);
        exit(1);
    }

    char buffer[MAP_WIDTH * MAP_HEIGHT + 1];
    ssize_t bytes_read = read(fd, buffer, MAP_WIDTH * MAP_HEIGHT);
    close(fd);

    if (bytes_read != MAP_WIDTH * MAP_HEIGHT)
    {
        fprintf(stderr, "Error reading file: %s\n", file_name);
        exit(1);
    }

    int i = 0;
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            game->map[x][y] = buffer[i++] - '0';
            if (buffer[i - 1] == 'P')
            {
                game->player_x = x;
                game->player_y = y;
            }
        }
    }
}

// Function to draw the map
void draw_map(void *param)
{
    t_game *game = (t_game *)param;
    
    // Create a new image buffer for drawing
    mlx_image_t *image = mlx_new_image(game->mlx, MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE);
    if (image == NULL)
    {
        fprintf(stderr, "Error creating image buffer\n");
        exit(1);
    }
    
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            uint32_t color;

            if (game->map[x][y] == 1) // wall
                color = 0xFFFFFF;
            else // empty space or other elements
                color = 0x000000;

            // Put the pixel in the image buffer
            mlx_put_pixel(image, x * TILE_SIZE, y * TILE_SIZE, color);
        }
    }

    // Display the image buffer on the window
    mlx_image_to_window(game->mlx, image, 0, 0);

    // Delete the image buffer to avoid memory leaks
    mlx_delete_image(game->mlx, image);
}

int main(int argc, char **argv)
{
    t_game *game;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <map_file.ber>\n", argv[0]);
        return 1;
    }

    // Initialize game structure
    game = (t_game *)malloc(sizeof(t_game));
    if (game == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Initialize MLX instance
    game->mlx = mlx_init(MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE, "2D Game", false);
    if (game->mlx == NULL)
    {
        fprintf(stderr, "MLX initialization failed\n");
        free(game);
        return 1;
    }

    // Load the map
    load_map(game, argv[1]);

    // Register draw_map function as loop hook to continuously draw the map
    mlx_loop_hook(game->mlx, draw_map, (void *)game);

    // Start rendering loop
    mlx_loop(game->mlx);

    // Free allocated memory
    free(game);

    return 0;
}
