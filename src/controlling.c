/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controlling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 23:24:02 by sshahary          #+#    #+#             */
/*   Updated: 2024/06/12 08:14:53 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	valid_position(t_game *data, double y, double x)
{
	char	**map;
	int		gap;

	gap = 6;
	if (y / TILE <= 0 || y <= gap || y / TILE >= data->cub->map_length
		|| x / TILE <= 0 || x <= gap || x / TILE >= data->cub->map_width)
		return (0);
	map = data->cub->map;
	if (map[(int)y / TILE][((int)x - gap) / TILE] == '1'
		|| map[(int)y / TILE][((int)x + gap) / TILE] == '1'
		|| map[((int)y - gap) / TILE][(int)x / TILE] == '1'
		|| map[((int)y + gap) / TILE][(int)x / TILE] == '1')
		return (0);
	return (1);
}

void	rotate(t_game *data, int i)
{
	if (i == -1)
	{
		data->player->angle -= ROT;
		if (data->player->angle < 0)
			data->player->angle += 2 * M_PI;
	}
	else
	{
		data->player->angle += ROT;
		if (data->player->angle > 0)
			data->player->angle -= 2 * M_PI;
	}
}

void	get_move(t_game *data, double *movex, double *movey)
{
	if (data->player->leftright == 1)
	{
		*movex = -sin(data->player->angle) * SPEED;
		*movey = cos(data->player->angle) * SPEED;
	}
	if (data->player->leftright == -1)
	{
		*movex = sin(data->player->angle) * SPEED;
		*movey = -cos(data->player->angle) * SPEED;
	}
	if (data->player->updown == 1)
	{
		*movex += cos(data->player->angle) * SPEED;
		*movey += sin(data->player->angle) * SPEED;
	}
	if (data->player->updown == -1)
	{
		*movex += -cos(data->player->angle) * SPEED;
		*movey += -sin(data->player->angle) * SPEED;
	}
}

void	control(t_game *data)
{
	double	movey;
	double	movex;
	int		newx;
	int		newy;

	if (data->player->rotate)
		rotate(data, data->player->rotate);
	get_move(data, &movex, &movey);
	newx = roundf(data->player->x + movex);
	newy = roundf(data->player->y + movey);
	if (valid_position(data, newy, newx))
	{
		data->player->x = newx;
		data->player->y = newy;
	}
}
