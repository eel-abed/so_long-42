/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   height_width.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:13:16 by eel-abed          #+#    #+#             */
/*   Updated: 2024/06/29 18:25:43 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_map_wall_error(void)
{
	printf("Error: Map must be surrounded by walls.\n");
	ft_error();
}

void	calculate_height(int fd, Dimensions *dim)
{
	char	ch;

	while (read(fd, &ch, 1) > 0)
	{
		if (ch == '\n')
		{
			dim->tmp_max_height++;
		}
	}
}

void	handle_first_line(int fd, Dimensions *dim)
{
	if (dim->first_line_width == -1)
		dim->first_line_width = dim->current_width;
	else if (dim->current_width != dim->first_line_width)
	{
		printf("Error: Map must be rectangular.\n");
		close(fd);
		ft_error();
		return ;
	}
	if (dim->current_width > dim->max_width)
		dim->max_width = dim->current_width;
	dim->current_width = 0;
	dim->max_height++;
}

void	handle_other_lines(int fd, Dimensions *dim, char ch)
{
	if (dim->first_line_width == -1 && ch != '1')
	{
		close(fd);
		ft_map_wall_error();
	}
	if (dim->max_height == dim->tmp_max_height - 1)
	{
		if (ch != '1' && ch != '\n')
		{
			close(fd);
			ft_map_wall_error();
		}
	}
}

void	calculate_width(int fd, Dimensions *dim)
{
	char	ch;

	while (read(fd, &ch, 1) > 0)
	{
		if ((dim->current_width == 0
				|| dim->current_width == dim->max_width - 1)
			&& ch != '1' && ch != '\n')
		{
			close(fd);
			ft_map_wall_error();
		}
		if (ch == '\n')
		{
			handle_first_line(fd, dim);
		}
		else
		{
			dim->current_width++;
			handle_other_lines(fd, dim, ch);
		}
	}
}
