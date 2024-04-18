/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:36:19 by eel-abed          #+#    #+#             */
/*   Updated: 2024/04/18 15:27:49 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void free_map(t_map *map)
{
    for (int i = 0; i < map->height; i++)
        free(map->grid[i]);
    free(map->grid);
    free(map);
}

t_map *parse_map(int fd)
{
    t_map *map = (t_map *)malloc(sizeof(t_map));
    if (!map)
        return (NULL);
    
    map->height = 0;
    map->grid = NULL;
    char *line;
    int ret;

    while ((line = get_next_line(fd)) != NULL)
    {
        char **new_grid = realloc(map->grid, sizeof(char *) * (map->height + 1));
        if (!new_grid)
        {
            free_map(map);
            return (NULL);
        }
        map->grid = new_grid;
        map->grid[map->height] = line;
        map->height++;
    }

    if (line == NULL)
    {
        free_map(map);
        return (NULL);
    }

    return (map);
}

void draw_map(mlx_t *mlx, t_map *map)
{
    int tile_size = 32; // Taille d'une tuile en pixels
    int x, y;

    // Charger les textures depuis les fichiers .xpm
    mlx_texture_t *wall_texture = mlx_load_xpm42("mur.xpm");
    mlx_texture_t *space_texture = mlx_load_xpm42("assets/Tiletest2.xpm");
    mlx_texture_t *player_texture = mlx_load_xpm42("assets/joueur.xpm");
    mlx_texture_t *exit_texture = mlx_load_xpm42("sortie.xpm");

    for (y = 0; y < map->height; y++)
    {
        for (x = 0; x < map->width; x++)
        {
            // Calcul des coordonnées de l'image à afficher
            int img_x = x * tile_size;
            int img_y = y * tile_size;

            // Récupération du caractère correspondant à la tuile
            char tile = map->grid[y][x];

            // Dessiner l'image correspondante en fonction du caractère
            if (tile == '1') // Mur
                mlx_texture_to_image(mlx, wall_texture);
            else if (tile == '0') // Espace vide
                mlx_texture_to_image(mlx, space_texture);
            else if (tile == 'P') // Joueur
                mlx_texture_to_image(mlx, player_texture);
            else if (tile == 'E') // Sortie
                mlx_texture_to_image(mlx, exit_texture);
        }
    }

    // Supprimer les textures après usage
    mlx_delete_texture(wall_texture);
    mlx_delete_texture(space_texture);
    mlx_delete_texture(player_texture);
    mlx_delete_texture(exit_texture);
}

int main()
{
    // Initialisation de MiniLibX et création de la fenêtre
    mlx_t* mlx = mlx_init(800, 600, "So_long", true);

    // Vérification si l'initialisation a réussi
    if (mlx == NULL) {
        // Affichage d'un message d'erreur
        printf("Erreur lors de l'initialisation de MiniLibX\n");
        return 1;
    }

    // Ouvrir le fichier .ber en lecture
    int fd = open("assets/map.ber", O_RDONLY);
    if (fd == -1) {
        // Affichage d'un message d'erreur si l'ouverture échoue
        printf("Erreur lors de l'ouverture du fichier\n");
        return 1;
    }

    // Parser la carte à partir du fichier .ber
    t_map *map = parse_map(fd);
    if (map == NULL) {
        // Affichage d'un message d'erreur si la lecture de la carte échoue
        printf("Erreur lors de la lecture de la carte\n");
        close(fd);
        return 1;
    }

    // Afficher la carte
    draw_map(mlx, map);

    // Boucle principale de la fenêtre
    mlx_loop(mlx);

    // Nettoyage des ressources et sortie
    free_map(map);
    close(fd);

    return 0;
}
