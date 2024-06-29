/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:43:29 by eel-abed          #+#    #+#             */
/*   Updated: 2024/06/29 15:44:34 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	fill(t_point cur, t_fill_params *params)
{
	if (cur.y < 0)
		return ;
	if (cur.y >= params->size.y)
		return ;
	if (cur.x < 0)
		return ;
	if (cur.x >= params->size.x)
		return ;
	if (params->tab[cur.y][cur.x] == '1')
		return ;
	if (params->tab[cur.y][cur.x] == 'F')
		return ;
	if (params->tab[cur.y][cur.x] == 'C')
		(*params->collectible_count)++;
	if (params->tab[cur.y][cur.x] == 'E')
		*params->exit_reachable = 1;
	params->tab[cur.y][cur.x] = 'F';
	fill((t_point){cur.x - 1, cur.y}, params);
	fill((t_point){cur.x + 1, cur.y}, params);
	fill((t_point){cur.x, cur.y - 1}, params);
	fill((t_point){cur.x, cur.y + 1}, params);
}

int	flood_fill(char **tab, t_point size, t_point begin, int collectible_total)
{
	int				collectible_count;
	int				exit_reachable;
	t_fill_params	params;

	params.tab = tab;
	params.size = size;
	params.to_fill = tab[begin.y][begin.x];
	params.collectible_count = &collectible_count;
	params.exit_reachable = &exit_reachable;
	collectible_count = 0;
	exit_reachable = 0;
	fill(begin, &params);
	return (collectible_count == collectible_total && exit_reachable);
}
