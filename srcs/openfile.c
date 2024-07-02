/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:42:11 by eel-abed          #+#    #+#             */
/*   Updated: 2024/07/02 17:51:49 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int openFile(char *map_name)
{
	int fd;

	fd = open(map_name, O_RDONLY);
	if (fd == -1)
	{
		printf("Could not open file %s\n", map_name);
		ft_error();
	}
	return (fd);
}
