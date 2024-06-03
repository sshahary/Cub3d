/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubdata.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:29:32 by asemsey           #+#    #+#             */
/*   Updated: 2024/06/03 16:41:40 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBDATA_H
# define CUBDATA_H

# include "cub.h"

typedef struct s_point
{
	double	x;//left right
	double	y;//up down
}	t_point;

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

// playerdir:
// 		0 E
// 		1 S
// 		2 W
// 		3 N

typedef struct s_texture
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
}	t_texture;


#endif