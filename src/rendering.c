/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:32:17 by sshahary          #+#    #+#             */
/*   Updated: 2024/06/03 15:46:53 by asemsey          ###   ########.fr       */
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
		pixel_put(data, ray, i++, data->cub->c_rgb);// read colors
}

void	get_color(t_game *data)
{
	data->ray->rayangle = nor_angle(data->ray->rayangle);
	if (data->ray->wallflag == 0)
	{
		if (data->ray->rayangle > M_PI / 2 && data->ray->rayangle < 3 * (M_PI / 2))
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

// int	get_color(t_game *data, int flag)
// {
// 	data->ray->rayangle = nor_angle(data->ray->rayangle); 
// 	if (flag == 0)
// 	{
// 		if (data->ray->rayangle > M_PI / 2 && data->ray->rayangle < 3 * (M_PI / 2))
// 		{
			
// 			return (0xB5B5B5FF); // west wall
// 		}
// 		else
// 			return (0xB5B4B5FF); // east wall
// 	}
// 	else
// 	{
// 		if (data->ray->rayangle > 0 && data->ray->rayangle < M_PI)
// 			return (0xF5F5F5FF); // south wall
// 		else
// 			return (0xF5F5F5FF); // north wall
// 	}
// }

// void	draw_wall(t_game *data, int ray, int tpix, int bpix)
// {
// 	int	color;

// 	color = get_color(data, data->ray->wallflag);
// 	while (tpix < bpix)
// 		pixel_put(data, ray, tpix++, color);
// }

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int get_texel_color(mlx_texture_t *texture, int tex_x, int tex_y)
{
	unsigned int	i;
	
	i = (tex_y * texture->width + tex_x ) * 4;
	return (get_rgba(texture->pixels[i], texture->pixels[i + 1], texture->pixels[i + 2], texture->pixels[i + 3]));
}

// calculate_texture_x
static int	get_texture_x(t_game *data)
{
	int		texture_x;

	if (data->ray->wallflag == 0)
		texture_x = fmod(data->ray->v_dist, TILE);
	else
		texture_x = fmod(data->ray->h_dist, TILE);
	// texture_x = (int)(relative_pos / TILE * texture_width);
	if (data->texture == data->textures.west || data->texture == data->textures.south)
		texture_x = TILE - texture_x - 1;
	// texture_x = texture_width - texture_x - 1;
	return (texture_x);
}

// void	draw_wall(t_game *data, int ray, int top, int bot)
// {
// 	int		tex_x;
// 	int		tex_y;
// 	double	step;
// 	double	tex_pos;

// 	get_texture(data);
// 	step = (double)data->tex[data->f_tex]->height / (bot - top);
// 	tex_x = c_tex_x(data, data->tex[data->f_tex]->width);
// 	if ((bot - top) > HEIGHT)
// 		tex_y = top - (HEIGHT / 2) + ((bot - top) / 2) * step;
// 	else
// 		tex_y = HEIGHT;
// 	tex_pos = 0;
// 	while (top < bot && top < HEIGHT)
// 	{
// 		tex_y = (int)tex_pos % data->tex[data->f_tex]->height;
// 		tex_pos += step;
// 		if (top < 0)
// 		{
// 			top++;
// 			continue ;
// 		}
// 		mlx_put_pixel(data->window, ray, top++,
// 			get_texel_color(data->tex[data->f_tex], tex_x, tex_y));
// 	}
// }

void draw_textured_wall(t_game *data, int ray, int tpix, int bpix)
{
	int tex_x;
	int tex_y;
	double step;
	double tex_pos;

	get_color(data);
	step = (double)data->texture->height / (bpix - tpix);
	tex_x = get_texture_x(data);
	if ((bpix - tpix) > SCREEN_HEIGHT)
		tex_y = tpix - (SCREEN_HEIGHT / 2) + ((bpix - tpix) / 2) * step;
	else
		tex_y = SCREEN_HEIGHT;
	tex_pos = 0;
	while (tpix < bpix && tpix < SCREEN_HEIGHT)
	{
		tex_y = (int)tex_pos % data->texture->height;
		tex_pos += step;
		if (tpix < 0)
		{
			tpix++;
			continue ;
		}
		mlx_put_pixel(data->img, ray, tpix++,
			get_texel_color(data->texture, tex_x, tex_y));
	}
}

void	render(t_game *data, int ray) // render the wall
{
	double wallh;
	double bpix;
	double tpix;

	data->ray->dist *= cos(nor_angle(data->ray->rayangle - data->player->angle)); // fix the fisheye
	if (data->ray->dist == 0)
		data->ray->dist = 1;// temporary fix, do not divide by 0!!!
	wallh = (TILE / data->ray->dist) * ((SCREEN_WIDTH / 2) / tan(data->player->fovradian / 2)); // get the wall height
	bpix = (SCREEN_HEIGHT / 2) + (wallh / 2); // get the bottom pixel
	tpix = (SCREEN_HEIGHT / 2) - (wallh / 2); // get the top pixel
	// if (bpix > SCREEN_HEIGHT) // check the bottom pixel
	// 	bpix = SCREEN_HEIGHT;
	// if (tpix < 0) // check the top pixel
	// 	tpix = 0;
	draw_textured_wall(data, ray, tpix, bpix);
	// draw_wall(data, ray, tpix, bpix); // draw the wall
	draw_floor_ceiling(data, ray, tpix, bpix); // draw the floor and the ceiling
}
