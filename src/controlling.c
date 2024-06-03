/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controlling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 23:24:02 by sshahary          #+#    #+#             */
/*   Updated: 2024/06/03 15:44:09 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	rotate(t_game *data, int i)
{
	if (i == 0)
	{
		data->player->angle -= ROT; // rotate left
		if (data->player->angle < 0)
			data->player->angle += 2 * M_PI;
	}
	else
	{
		data->player->angle += ROT; // rotate left
		if (data->player->angle > 0)
			data->player->angle -= 2 * M_PI;
	}
}

void	move(t_game *data, t_point far_pos, t_point new_pos)
{
	int mapgridy;
	int mapgridx;
	int newx;
	int newy;

	// Calculate new player position
	newx = roundf(data->player->x + new_pos.x);
	newy = roundf(data->player->y + new_pos.y);

	// Convert new position to map grid coordinates
	mapgridx = roundf(data->player->x + far_pos.x) / TILE;
	mapgridy = roundf(data->player->y + far_pos.y) / TILE;

	// Check for wall collisions at the new position and adjacent positions
	if (data->cub->map[mapgridy][mapgridx] != '1'
		&& data->cub->map[mapgridy][(int)data->player->x / TILE] != '1'
		&& data->cub->map[(int)data->player->y / TILE][mapgridx] != '1')
	{
		// Update player position if no collision
		data->player->x = roundf(data->player->x + new_pos.x);
		data->player->y = roundf(data->player->y + new_pos.y);
	}
}

void	get_move(t_game *data, double *movex, double *movey, int far)
{
	if (data->player->leftright == 1)
	{ // Move right
		*movex = -sin(data->player->angle) * SPEED - (far * 0.1);
		*movey = cos(data->player->angle) * SPEED + (far * 0.1);
	}
	if (data->player->leftright == -1)
	{ // Move left
		*movex = sin(data->player->angle) * SPEED + (far * 0.1);
		*movey = -cos(data->player->angle) * SPEED - (far * 0.1);
	}
	if (data->player->updown == 1)
	{ // Move up
		*movex += cos(data->player->angle) * SPEED + (far * 0.1);
		*movey += sin(data->player->angle) * SPEED + (far * 0.1);
	}
	if (data->player->updown == -1)
	{ // Move down
		*movex += -cos(data->player->angle) * SPEED - (far * 0.1);
		*movey += -sin(data->player->angle) * SPEED - (far * 0.1);
	}
}

void	control(t_game *data)
{
	t_point	new_pos;
	t_point	far_pos;

	// Rotation
	if (data->player->rotate == 1) // Rotate right
		rotate(data, 1);
	if (data->player->rotate == -1) // Rotate left
		rotate(data, 0);
	// Movement
	get_move(data, &new_pos.x, &new_pos.y, 0);
	get_move(data, &far_pos.x, &far_pos.y, 1);
	// Move the player
	move(data, far_pos, new_pos);
}
