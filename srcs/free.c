/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:31:09 by eel-abed          #+#    #+#             */
/*   Updated: 2024/07/08 22:31:45 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void free_map_data(char **map_data)
{
	int i;

	i = 0;
	while (map_data[i])
	{
		free(map_data[i]);
		i++;
	}
	free(map_data);
}
