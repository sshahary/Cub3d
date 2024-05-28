/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:32:17 by sshahary          #+#    #+#             */
/*   Updated: 2024/05/28 20:24:48 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

// void	render(t_cub *cub)
// {
	
// }

void	pixel_put(t_game *data, int x, int y, int color)
{
	if (x < 0)
		return ;
	else if (x >= SCREEN_WIDTH)
		return ;
	if (y < 0)
		return ;
	else if (y >= SCREEN_HEIGHT)
		return ;
	mlx_put_pixel(data->img, x, y, color);
}

void	draw_floor_ceiling(t_game *data, int ray, int t_pix, int b_pix)
{
 int  i;
//  int  c;

	i = b_pix;
	while (i < SCREEN_HEIGHT)
		pixel_put(data, ray, i++, 0xB99470FF);
	i = 0;
	while (i < t_pix)
		pixel_put(data, ray, i++, 0x89CFF3FF);
}

int	get_color(t_game *data, int flag)
{
	data->ray->rayangle = nor_angle(data->ray->rayangle); 
	if (flag == 0)
	{
		if (data->ray->rayangle > M_PI / 2 && data->ray->rayangle < 3 * (M_PI / 2))
			return (0xB5B5B5FF); // west wall
		else
			return (0xB5B5B5FF); // east wall
	}
	else
	{
		if (data->ray->rayangle > 0 && data->ray->rayangle < M_PI)
			return (0xF5F5F5FF); // south wall
		else
			return (0xF5F5F5FF); // north wall
	}
}

void draw_wall(t_game *data, int ray, int t_pix, int b_pix)
{
	int color;

	color = get_color(data, data->ray->wallflag);
	while (t_pix < b_pix)
		pixel_put(data, ray, t_pix++, color);
}

void render(t_game *data, int ray) // render the wall
{
	double wall_h;
	double b_pix;
	double t_pix;

	data->ray->dist *= cos(nor_angle(data->ray->rayangle - data->player->angle)); // fix the fisheye
	wall_h = (TILE / data->ray->dist) * ((SCREEN_WIDTH / 2) / tan(data->player->fovradian / 2)); // get the wall height
	b_pix = (SCREEN_HEIGHT / 2) + (wall_h / 2); // get the bottom pixel
	t_pix = (SCREEN_HEIGHT / 2) - (wall_h / 2); // get the top pixel
	if (b_pix > SCREEN_HEIGHT) // check the bottom pixel
		b_pix = SCREEN_HEIGHT;
	if (t_pix < 0) // check the top pixel
		t_pix = 0;
	draw_wall(data, ray, t_pix, b_pix); // draw the wall
	draw_floor_ceiling(data, ray, t_pix, b_pix); // draw the floor and the ceiling
}
