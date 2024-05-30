/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:55:15 by asemsey           #+#    #+#             */
/*   Updated: 2024/05/30 12:30:36 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
	{
		printf("%d\t%s\n", i, map[i]);
		i++;
	}
}

void	display_struct(t_cub *cub)
{
	printf("t_cub:\n");
	printf("player facing %d at %d, %d\n", cub->player_dir, cub->y, cub->x);
	printf("ea: %s\n", cub->ea_png);
	printf("we: %s\n", cub->we_png);
	printf("no: %s\n", cub->no_png);
	printf("so: %s\n", cub->so_png);
	printf("ceiling: %x\n", cub->c_rgb);
	printf("floor: %x\n", cub->f_rgb);
}
