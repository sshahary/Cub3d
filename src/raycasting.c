/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:33:26 by sshahary          #+#    #+#             */
/*   Updated: 2024/06/11 17:06:02 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

float	nor_angle(float angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

float	find_h_intersect(t_game *data, float angle)
{
	float	hx;
	float	hy;
	float	xstep;
	float	ystep;
	int		pix;

	ystep = TILE;
	xstep = TILE / tan(angle);
	hy = floor(data->player->y / TILE) * TILE;
	pix = check_intersect(angle, &hy, &ystep, 1);
	hx = data->player->x + (hy - data->player->y) / tan(angle);
	if ((check_circle(angle, 'y') && xstep > 0)
		|| (!check_circle(angle, 'y') && xstep < 0))
		xstep *= -1;
	while (wall_hit(hx, hy - pix, data))
	{
		hx += xstep;
		hy += ystep;
	}
	data->ray->h_dist = hx;
	return (sqrt(pow(hx - data->player->x, 2) + pow(hy - data->player->y, 2)));
}

float	find_v_intersect(t_game *data, float angle)
{
	float	vx;
	float	vy;
	float	xstep;
	float	ystep;
	int		pix;

	xstep = TILE;
	ystep = TILE * tan(angle);
	vx = floor(data->player->x / TILE) * TILE;
	pix = check_intersect(angle, &vx, &xstep, 0);
	vy = data->player->y + (vx - data->player->x) * tan(angle);
	if ((check_circle(angle, 'x') && ystep < 0)
		|| (!check_circle(angle, 'x') && ystep > 0))
		ystep *= -1;
	while (wall_hit(vx - pix, vy, data))
	{
		vx += xstep;
		vy += ystep;
	}
	data->ray->v_dist = vy;
	return (sqrt(pow(vx - data->player->x, 2) + pow(vy - data->player->y, 2)));
}

void	ray_cast(t_game *data)
{
	int		i;
	double	hdist;
	double	vdist;

	i = 0;
	data->ray->rayangle = data->player->angle - (data->player->fovradian / 2);
	while (i < SCREEN_WIDTH)
	{
		data->ray->wallflag = 0;
		hdist = find_h_intersect(data, nor_angle(data->ray->rayangle));
		vdist = find_v_intersect(data, nor_angle(data->ray->rayangle));
		if (vdist <= hdist)
			data->ray->dist = vdist;
		else
		{
			data->ray->dist = hdist;
			data->ray->wallflag = 1;
		}
		render(data, i);
		i++;
		data->ray->rayangle += (data->player->fovradian / SCREEN_WIDTH);
	}
}
