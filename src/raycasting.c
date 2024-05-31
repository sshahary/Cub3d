/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 23:49:39 by sshahary          #+#    #+#             */
/*   Updated: 2024/05/31 14:53:49 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

float	nor_angle(float angle)
{
	// Normalize the angle to be within [0, 2π)
	while (angle < 0) {
		angle += 2 * M_PI;
	}
	while (angle >= 2 * M_PI) {
		angle -= 2 * M_PI;
	}
	return angle;
}

//get horizantal intersection distance
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
	if ((check_circle(angle, 'y') && xstep > 0) || (!check_circle(angle, 'y') && xstep < 0)) // check x_step value
		xstep *= -1;
	while (wall_hit(hx, hy - pix, data)) // check the wall hit whit the pixel value
	{
		hx += xstep;
		hy += ystep;
	}
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
	pix = check_intersect(angle, &vx, &xstep, 0); // check the intersection and get the pixel value
	vy = data->player->y + (vx - data->player->x) * tan(angle);
	if ((check_circle(angle, 'x') && ystep < 0) || (!check_circle(angle, 'x') && ystep > 0)) // check y_step value
		ystep *= -1;
	while (wall_hit(vx - pix, vy, data)) // check the wall hit whit the pixel value
	{
		vx += xstep;
		vy += ystep;
	}
	return (sqrt(pow(vx - data->player->x, 2) + pow(vy - data->player->y, 2)));
}

void	ray_cast(t_game *data)
{
	int		i;

	i = 0;
	data->ray->rayangle = data->player->angle - (data->player->fovradian / 2); // the start angle
	while (i < SCREEN_WIDTH) // loop for the rays
	{
		data->ray->wallflag = 0; // flag for the wall
		data->ray->h_dist = find_h_intersect(data, nor_angle(data->ray->rayangle)); // get the horizontal intersection
		data->ray->v_dist = find_v_intersect(data, nor_angle(data->ray->rayangle)); // get the vertical intersection
		// printf("dist: %f, %f\n", hint, vint);
		if (data->ray->v_dist <= data->ray->h_dist) // check the distance
			data->ray->dist = data->ray->v_dist; // get the distance
		else
		{
			data->ray->dist = data->ray->h_dist; // get the distance
			data->ray->wallflag = 1; // flag for the wall
		}
		// printf("%f\n: ", data->ray->rayangle);
		render(data, i); // render the wall
		i++; // next ray
		data->ray->rayangle += (data->player->fovradian / SCREEN_WIDTH); // next angle
	}
}
