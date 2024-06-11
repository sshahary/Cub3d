/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:32:17 by sshahary          #+#    #+#             */
/*   Updated: 2024/06/11 16:43:23 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	pixel_put(t_game *data, int x, int y, int color)
{
	if (x < 0 || x >= SCREEN_WIDTH)
		return ;
	if (y < 0 || y >= SCREEN_HEIGHT)
		return ;
	mlx_put_pixel(data->img, x, y, color);
}

void	draw_floor_ceiling(t_game *data, int ray, int tpix, int bpix)
{
	int	i;

	i = bpix;
	while (i < SCREEN_HEIGHT)
		pixel_put(data, ray, i++, data->cub->f_rgb);
	i = 0;
	while (i < tpix)
		pixel_put(data, ray, i++, data->cub->c_rgb);
}

void	get_color(t_game *data)
{
	data->ray->rayangle = nor_angle(data->ray->rayangle);
	if (data->ray->wallflag == 0)
	{
		if (data->ray->rayangle > M_PI / 2
			&& data->ray->rayangle < 3 * (M_PI / 2))
			data->texture = data->textures.west;
		else
			data->texture = data->textures.east;
	}
	else
	{
		if (data->ray->rayangle > 0 && data->ray->rayangle < M_PI)
			data->texture = data->textures.south;
		else
			data->texture = data->textures.north;
	}
}

void	render(t_game *data, int ray)
{
	double	wallh;
	double	bpix;
	double	tpix;

	data->ray->dist *= cos(nor_angle(data->ray->rayangle \
		- data->player->angle));
	if (data->ray->dist == 0)
		data->ray->dist = 1;
	wallh = (TILE / data->ray->dist) * ((SCREEN_WIDTH / 2) \
		/ tan(data->player->fovradian / 2));
	bpix = (SCREEN_HEIGHT / 2) + (wallh / 2);
	tpix = (SCREEN_HEIGHT / 2) - (wallh / 2);
	draw_textured_wall(data, ray, tpix, bpix);
	draw_floor_ceiling(data, ray, tpix, bpix);
}
