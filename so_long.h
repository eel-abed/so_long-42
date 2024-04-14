/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:16:45 by eel-abed          #+#    #+#             */
/*   Updated: 2024/04/14 15:20:23 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define SO_LONG_H

/* Incluez ici les bibliothèques nécessaires */
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>

/* Définissez ici les prototypes de vos fonctions */

void game_init(void);
void game_run(void);
void game_end(void);

void map_load(const char *filename);
void map_unload(void);
void map_draw(void);

void render_begin(void);
void render_end(void);

void utils_do_something(void);

#endif /* SO_LONG_H */
