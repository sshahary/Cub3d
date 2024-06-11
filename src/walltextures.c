/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walltextures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:36:57 by sshahary          #+#    #+#             */
/*   Updated: 2024/06/11 16:43:58 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	get_texel_color(mlx_texture_t *texture, int tex_x, int tex_y)
{
	unsigned int	i;

	i = (tex_y * texture->width + tex_x) * 4;
	return (get_rgba(texture->pixels[i], texture->pixels[i + 1],
			texture->pixels[i + 2], texture->pixels[i + 3]));
}

static int	get_texture_x(t_game *data)
{
	int		texture_x;
	int		temp_pos;

	if (data->ray->wallflag == 0)
		temp_pos = fmod(data->ray->v_dist, TILE);
	else
		temp_pos = fmod(data->ray->h_dist, TILE);
	texture_x = (int)(temp_pos / TILE * data->texture->width);
	if (data->texture == data->textures.west
		|| data->texture == data->textures.south)
		temp_pos = TILE - temp_pos - 1;
	texture_x = data->texture->width - temp_pos - 1;
	return (texture_x);
}

void	draw_textured_wall(t_game *data, int ray, int tpix, int bpix)
{
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;

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
