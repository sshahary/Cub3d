/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:55:15 by asemsey           #+#    #+#             */
/*   Updated: 2024/06/12 08:45:52 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	print_map(char **map, int map_width)
{
	int	i;

	i = 0;
	printf("x\t");
	while (i < map_width)
	{
		printf("%d", i % 10);
		i++;
	}
	printf("\n\n");
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
