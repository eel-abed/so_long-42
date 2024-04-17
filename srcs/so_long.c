/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:36:19 by eel-abed          #+#    #+#             */
/*   Updated: 2024/04/17 18:29:19 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


int main()
{
    // Initialisation de MiniLibX et création de la fenêtre
    mlx_t* mlx = mlx_init(800, 600, "So_long", true);

    // Vérification si l'initialisation a réussi
    if (mlx == NULL) {
        // Affichage d'un message d'erreur
        return 1;
    }

    // Boucle principale de la fenêtre
    mlx_loop(mlx);

    return 0;
}
