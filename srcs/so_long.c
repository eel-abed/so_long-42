/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:36:19 by eel-abed          #+#    #+#             */
/*   Updated: 2024/04/17 17:52:24 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line.h"
#include "MLX42.h"

#define max(a, b) ((a) > (b) ? (a) : (b))
#define TILE_SIZE 32 // Définition de la taille d'une tuile
#define COLOR_EMPTY 0x00FFFFFF // Blanc pour les emplacements vides
#define COLOR_WALL 0x00000000 // Noir pour les murs
#define COLOR_COLLECTIBLE 0x00FFFF00 // Jaune pour les objets à collecter
#define COLOR_EXIT 0x0000FF00 // Vert pour la sortie
#define COLOR_PLAYER 0x000000FF // Bleu pour la position de départ du joueur


typedef struct {
    char **map;
    int width;
    int height;
} Map;

Map *read_map(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return NULL;
    }

    Map *map = malloc(sizeof(Map));
    if (map == NULL) {
        perror("Memory allocation error");
        close(fd);
        return NULL;
    }

    // Initialize map dimensions
    map->width = 0;
    map->height = 0;

    // Temporary array to store lines
    char **temp_map = malloc(0);
    char *line;

    // Read the map line by line
    while ((line = get_next_line(fd)) != NULL) {
        // Reallocate memory for the new line
        temp_map = realloc(temp_map, (map->height + 1) * sizeof(char *));
        if (temp_map == NULL) {
            perror("Memory allocation error");
            free(line);
            close(fd);
            free(map);
            return NULL;
        }

        // Store the new line
        temp_map[map->height] = line;

        // Update map dimensions
        map->height++;
        map->width = max(map->width, (int)strlen(line));
    }

    close(fd);

    // Store the temporary map in the Map structure
    map->map = temp_map;

    return map;
}

void free_map(Map *map) {
    if (map == NULL) return;

    for (int i = 0; i < map->height; i++) {
        free(map->map[i]);
    }
    free(map->map);
    free(map);
}

// Fonction pour dessiner la carte sur l'image MiniLibX
void draw_map(mlx_image_t* image, Map* map) {
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            // Détermine la couleur en fonction de l'élément de la carte
            uint32_t color;
            switch (map->map[y][x]) {
                case '0':
                    color = COLOR_EMPTY;
                    break;
                case '1':
                    color = COLOR_WALL;
                    break;
                case 'C':
                    color = COLOR_COLLECTIBLE;
                    break;
                case 'E':
                    color = COLOR_EXIT;
                    break;
                case 'P':
                    color = COLOR_PLAYER;
                    break;
                default:
                    color = COLOR_EMPTY; // Par défaut, utilise la couleur pour un emplacement vide
            }

            // Dessine le carré correspondant sur l'image MiniLibX
            for (int dy = 0; dy < TILE_SIZE; dy++) {
                for (int dx = 0; dx < TILE_SIZE; dx++) {
                    mlx_put_pixel(image, x * TILE_SIZE + dx, y * TILE_SIZE + dy, color);
                }
            }
        }
    }
}


int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <mapfile>\n", argv[0]);
        return 1;
    }

    Map *map = read_map(argv[1]);
    if (map == NULL) {
        return 1;
    }

    // Initialisation de MiniLibX
    mlx_t* mlx = mlx_init(800, 600, "so_long", true);
    if (mlx == NULL) {
        perror("Error initializing MiniLibX");
        free_map(map);
        return 1;
    }

    // Création de l'image MiniLibX à partir de la carte
    mlx_image_t* image = mlx_new_image(mlx, map->width * TILE_SIZE, map->height * TILE_SIZE);
    if (image == NULL) {
        perror("Error creating MiniLibX image");
        free_map(map);
        mlx_terminate(mlx);
        return 1;
    }

    // Dessine la carte sur l'image MiniLibX
    draw_map(image, map);

    // Affichage de la carte dans la fenêtre
    // Utilise une fonction pour dessiner la carte sur l'image MiniLibX

    // Affiche l'image dans la fenêtre
    mlx_image_to_window(mlx, image, 0, 0);

    // Boucle principale de MiniLibX pour gérer les événements
    mlx_loop(mlx);

    // Libération de la mémoire et terminaison de MiniLibX
    free_map(map);
    mlx_delete_image(mlx, image);
    mlx_terminate(mlx);

    return 0;
}
