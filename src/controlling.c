/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controlling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 23:24:02 by sshahary          #+#    #+#             */
/*   Updated: 2024/06/11 16:19:23 by asemsey          ###   ########.fr       */
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
	if (i == 0)
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

void	move(t_game *data, t_point far_pos, t_point new_pos)
{
	int	newx;
	int	newy;

	(void) far_pos;
	newx = roundf(data->player->x + new_pos.x);
	newy = roundf(data->player->y + new_pos.y);
	if (valid_position(data, newy, newx))
	{
		data->player->x = roundf(data->player->x + new_pos.x);
		data->player->y = roundf(data->player->y + new_pos.y);
	}
}

void	get_move(t_game *data, double *movex, double *movey, int far)
{
	if (data->player->leftright == 1)
	{
		*movex = -sin(data->player->angle) * SPEED - (far * 0.1);
		*movey = cos(data->player->angle) * SPEED + (far * 0.1);
	}
	if (data->player->leftright == -1)
	{
		*movex = sin(data->player->angle) * SPEED + (far * 0.1);
		*movey = -cos(data->player->angle) * SPEED - (far * 0.1);
	}
	if (data->player->updown == 1)
	{
		*movex += cos(data->player->angle) * SPEED + (far * 0.1);
		*movey += sin(data->player->angle) * SPEED + (far * 0.1);
	}
	if (data->player->updown == -1)
	{
		*movex += -cos(data->player->angle) * SPEED - (far * 0.1);
		*movey += -sin(data->player->angle) * SPEED - (far * 0.1);
	}
}

void	control(t_game *data)
{
	t_point	new_pos;
	t_point	far_pos;

	if (data->player->rotate == 1)
		rotate(data, 1);
	if (data->player->rotate == -1)
		rotate(data, 0);
	get_move(data, &new_pos.x, &new_pos.y, 0);
	get_move(data, &far_pos.x, &far_pos.y, 1);
	move(data, far_pos, new_pos);
}
