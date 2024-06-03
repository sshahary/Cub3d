/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controlling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 23:24:02 by sshahary          #+#    #+#             */
/*   Updated: 2024/06/03 13:01:43 by asemsey          ###   ########.fr       */
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

void	move(t_game *data, double movex, double movey)
{
	int mapgridy;
	int mapgridx;
	int newx;
	int newy;

	// Calculate new player position
	newx = roundf(data->player->x + movex);
	newy = roundf(data->player->y + movey);

	// Convert new position to map grid coordinates
	mapgridx = newx / TILE;
	mapgridy = newy / TILE;

	// Check for wall collisions at the new position and adjacent positions
	if (data->cub->map[mapgridy][mapgridx] != '1'
		&& data->cub->map[mapgridy][(int)data->player->x / TILE] != '1'
		&& data->cub->map[(int)data->player->y / TILE][mapgridx] != '1')
	{
		// Update player position if no collision
		data->player->x = newx;
		data->player->y = newy;
	}
}

void	control(t_game *data, double movex, double movey)
{
	// Rotation
	if (data->player->rotate == 1) // Rotate right
		rotate(data, 1);
	if (data->player->rotate == -1) // Rotate left
		rotate(data, 0);
	// Movement
		if (data->player->leftright == 1)
		{ // Move right
			movex = -sin(data->player->angle) * SPEED;
			movey = cos(data->player->angle) * SPEED;
		}
		if (data->player->leftright == -1)
		{ // Move left
			movex = sin(data->player->angle) * SPEED;
			movey = -cos(data->player->angle) * SPEED;
		}
		if (data->player->updown == 1)
		{ // Move up
			movex += cos(data->player->angle) * SPEED;
			movey += sin(data->player->angle) * SPEED;
		}
		if (data->player->updown == -1)
		{ // Move down
			movex += -cos(data->player->angle) * SPEED;
			movey += -sin(data->player->angle) * SPEED;
		}
		// Move the player
		move(data, movex, movey);
}
