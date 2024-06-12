/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:29:32 by asemsey           #+#    #+#             */
/*   Updated: 2024/06/12 09:38:31 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_cub		t_cub;
typedef struct s_player		t_player;
typedef struct s_ray		t_ray;
typedef struct s_texture	t_texture;

// data from parsing
typedef struct s_cub
{
	char	**map;
	char	*no_png;
	char	*so_png;
	char	*ea_png;
	char	*we_png;
	int		c_rgb;
	int		f_rgb;
	int		map_length;
	int		map_width;
	int		player_dir;
	int		x;
	int		y;
}	t_cub;

typedef struct s_player
{
	int		x;
	int		y;
	double	angle;
	float	fovradian;
	int		rotate;
	int		leftright;
	int		updown;
}	t_player;

typedef struct s_ray
{
	double	rayangle;
	double	dist;
	double	h_dist;
	double	v_dist;
	int		wallflag;
}	t_ray;

// wall textures
typedef struct s_texture
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
}	t_texture;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

#endif