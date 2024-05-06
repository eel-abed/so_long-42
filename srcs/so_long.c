/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:36:19 by eel-abed          #+#    #+#             */
/*   Updated: 2024/05/06 12:41:39 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Create a new image
static mlx_image_t* img;
static mlx_image_t* obstacle;

// Exit the program as failure.
static void ft_error(void)
{
    fprintf(stderr, "%s", mlx_strerror(mlx_errno));
    exit(EXIT_FAILURE);
}


void ft_hook(void* param)
{
	mlx_t* mlx = param;
	unsigned int new_x = img->instances[0].x;
	unsigned int new_y = img->instances[0].y;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		new_y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		new_y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		new_x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		new_x += 5;

	// Check if the new position collides with any of the obstacles
	for (size_t i = 0; i < obstacle->count; i++) {
        if (!(new_x + img->width < (unsigned int)obstacle->instances[i].x || new_x > (unsigned int)obstacle->instances[i].x + 32 ||
              new_y + img->height < (unsigned int)obstacle->instances[i].y || new_y > (unsigned int)obstacle->instances[i].y + 32)) {
            // New position collides with an obstacle, do not move
            return;
        }
    }

	// Check if it is within the window boundaries
	if (new_x >= 0 && new_x <= WINDOW_WIDTH && new_y >= 0 && new_y <= WINDOW_HEIGHT) {
		img->instances[0].x = new_x;
		img->instances[0].y = new_y;
	}
}

int	main(void)
{
	// Start mlx
	mlx_t* mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Test", true);
	if (!mlx)
        ft_error();

	img = mlx_new_image(mlx, 32, 32);
	if (!img)
		ft_error();

	// Set every pixel to white
	memset(img->pixels, 255, img->width * img->height * sizeof(int32_t));
	
	// Create a obstacle
	obstacle = mlx_new_image(mlx, 32, 32);
	if (!obstacle)
		ft_error();

	// Set every pixel to blue
	uint32_t blueColor = 0x0000FFFF;
	for (uint32_t y = 0; y < obstacle->height; y++) {
		for (uint32_t x = 0; x < obstacle->width; x++) {
			mlx_put_pixel(obstacle, x, y, blueColor);
		}
	}

	// Allocate space for two instances
	obstacle->instances = malloc(2 * sizeof(*obstacle->instances));
	if (!obstacle->instances)
		ft_error();

	// Set the position of the first instance
	obstacle->instances[0].x = 100;
	obstacle->instances[0].y = 0;

	// Set the position of the second instance
	obstacle->instances[1].x = 200;
	obstacle->instances[1].y = 200;

	// Update the count of instances
	obstacle->count = 2;

	// Display an instance of the obstacle
	if (mlx_image_to_window(mlx, obstacle, obstacle->instances[0].x, obstacle->instances[0].y) < 0)
		ft_error();

	// Display the second instance of the obstacle
	if (mlx_image_to_window(mlx, obstacle, obstacle->instances[1].x, obstacle->instances[1].y) < 0)
		ft_error();

	// Display an instance of the image
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		ft_error();

	mlx_loop_hook(mlx, ft_hook, mlx);
		
	mlx_loop(mlx);
	

	// Optional, terminate will clean up any leftovers, this is just to demonstrate.
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
	free(mlx);
	return (EXIT_SUCCESS);
}


