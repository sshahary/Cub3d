/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:32:17 by sshahary          #+#    #+#             */
/*   Updated: 2024/05/29 19:47:33 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

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

void	draw_floor_ceiling(t_game *data, int ray, int tpix, int bpix)
{
	int	i;

	i = bpix;
	while (i < SCREEN_HEIGHT)
		pixel_put(data, ray, i++, data->cub->c_rgb);
	i = 0;
	while (i < tpix)
		pixel_put(data, ray, i++, data->cub->f_rgb);// read colors
}

// void	draw_floor_ceiling(t_game *data, int ray, int tpix, int bpix)
// {
// 	int	i;

// 	i = bpix;
// 	while (i < SCREEN_HEIGHT)
// 		pixel_put(data, ray, i++, 0xC09470FF);
// 	i = 0;
// 	while (i < tpix)
// 		pixel_put(data, ray, i++, 0x00000000);
// }

int	get_color(t_game *data, int flag)
{
	data->ray->rayangle = nor_angle(data->ray->rayangle); 
	if (flag == 0)
	{
		if (data->ray->rayangle > M_PI / 2 && data->ray->rayangle < 3 * (M_PI / 2))
		{
			
			return (0xB5B5B5FF); // west wall
		}
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

void	draw_wall(t_game *data, int ray, int tpix, int bpix)
{
	int	color;

	color = get_color(data, data->ray->wallflag);
	while (tpix < bpix)
		pixel_put(data, ray, tpix++, color);
}
int get_texel_color(mlx_texture_t *texture, int tex_x, int tex_y)
{
    return ((int*)texture->pixels)[tex_y * texture->width + tex_x];
}

// void draw_textured_wall(t_game *data, int ray, int tpix, int bpix) {
//     int color;
//     int tex_x;
//     int tex_y;
//     double step;
//     double tex_pos;
//     int wall_height = bpix - tpix;
//     mlx_texture_t *texture;

//     // Determine which texture to use
//     if (data->ray->wallflag == 0) {
//         if (data->ray->rayangle > M_PI / 2 && data->ray->rayangle < 3 * (M_PI / 2)) {
//             texture = data->textures.west;
//         } else {
//             texture = data->textures.east;
//         }
//     } else {
//         if (data->ray->rayangle > 0 && data->ray->rayangle < M_PI) {
//             texture = data->textures.south;
//         } else {
//             texture = data->textures.north;
//         }
//     }

//     // Calculate texture x coordinate
//     tex_x = (int)(data->ray->wallflag * (double)(texture->width));
//     if ((data->ray->wallflag == 0 && data->ray->rayangle > M_PI / 2 && data->ray->rayangle < 3 * (M_PI / 2)) ||
//         (data->ray->wallflag == 1 && data->ray->rayangle > M_PI)) {
//         tex_x = texture->width - tex_x - 1;
//     }

//     step = 1.0 * texture->height / wall_height;
//     tex_pos = (tpix - SCREEN_HEIGHT / 2 + wall_height / 2) * step;

//     while (tpix < bpix) {
//         tex_y = (int)tex_pos & (texture->height - 1);
//         tex_pos += step;
//         color = get_texel_color(texture, tex_x, tex_y);
//         pixel_put(data, ray, tpix++, color);
//     }
// }


void	render(t_game *data, int ray) // render the wall
{
	double wallh;
	double bpix;
	double tpix;

	data->ray->dist *= cos(nor_angle(data->ray->rayangle - data->player->angle)); // fix the fisheye
	wallh = (TILE / data->ray->dist) * ((SCREEN_WIDTH / 2) / tan(data->player->fovradian / 2)); // get the wall height
	bpix = (SCREEN_HEIGHT / 2) + (wallh / 2); // get the bottom pixel
	tpix = (SCREEN_HEIGHT / 2) - (wallh / 2); // get the top pixel
	if (bpix > SCREEN_HEIGHT) // check the bottom pixel
		bpix = SCREEN_HEIGHT;
	if (tpix < 0) // check the top pixel
		tpix = 0;
	// draw_textured_wall(data, ray, tpix, bpix);
	draw_wall(data, ray, tpix, bpix); // draw the wall
	draw_floor_ceiling(data, ray, tpix, bpix); // draw the floor and the ceiling
}

