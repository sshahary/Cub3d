/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycastutilis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 00:06:56 by sshahary          #+#    #+#             */
/*   Updated: 2024/05/27 00:07:35 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	check_circle(float angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
		return (1);
	}
	if (c = 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
		return (1);
	}
	return (0);
}

int	check_intersect(float angle, float *inter, float *step, int horiflag)
{
	if (horiflag)
	{
		
		if (angle > 0 && angle < M_PI)
		{
			*inter += TILE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2)) 
		{
			*inter += TILE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int	wall_hit(float x, float y, t_game *data)
{
	int  xmap;
	int  ymap;

	if (x < 0 || y < 0)
		return (0);
	xmap = floor (x / TILE); // get the x position in the map
	ymap = floor (y / TILE); // get the y position in the map
	if ((ymap >= data->cub->height || xmap >= data->cub->wid))
		return (0);
	if (data->cub->maps[ymap] && xmap <= (int)strlen(data->cub->maps[ymap]))
		if (data->cub->maps[ymap][xmap] == '1')
			return (0);
	return (1);
}

