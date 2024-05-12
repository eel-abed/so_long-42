/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:16:45 by eel-abed          #+#    #+#             */
/*   Updated: 2024/05/12 17:07:07 by eel-abed         ###   ########.fr       */
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


// Create a new image
mlx_image_t* player;
mlx_image_t* obstacle;
mlx_image_t* collectible;
mlx_image_t* sortie;

void ft_hook(void* param);
void get_window_dimensions(char *map_name, int *width, int *height);
void read_map(char *map_name, mlx_image_t *player, mlx_image_t *obstacle, mlx_image_t *collectible, mlx_image_t *sortie);
void create_elements(mlx_t *mlx);
void display_elements(mlx_t *mlx,mlx_image_t *obstacle, mlx_image_t *collectible);
void ft_error(void);





#endif
