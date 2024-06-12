/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:54:12 by sshahary          #+#    #+#             */
/*   Updated: 2024/06/12 09:54:24 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "../lib/ft_printf/ft_printf.h"
# include "../lib/gnl/get_next_line_bonus.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "structures.h"

# define SCREEN_WIDTH 1200
# define SCREEN_HEIGHT 980
# define TILE 32
# define FOV 60
# define SPEED 2
# define ROT 0.05

// main structure
typedef struct s_game
{
	mlx_t			*mlx;
	t_cub			*cub;
	t_player		*player;
	t_ray			*ray;
	mlx_image_t		*img;
	mlx_texture_t	*texture;
	t_texture		textures;
}	t_game;

// raycasting

int		check_circle(float angle, char c);
int		check_intersect(float angle, float *inter, float *step, int horiflag);
int		wall_hit(float x, float y, t_game *data);
float	nor_angle(float angle);
void	ray_cast(t_game *data);

// rendering

void	get_color(t_game *data);
void	draw_textured_wall(t_game *data, int ray, int tpix, int bpix);
void	render(t_game *data, int ray);

// controlling

void	control(t_game *data);
void	key(mlx_key_data_t keydata, void *param);

// parse

int		read_mapfile(char *filename, t_cub *cub);
int		map_length(char *filename);
void	get_identifier(char *line, t_cub *cub);
void	set_coordinates(t_cub *cub);
int		is_mapline(char *str);
int		is_identifier(char *str);
int		is_rgb(char *str, int iter);
int		map_valid(t_cub *cub);
int		cub_filename(char *str);

void	ft_free(t_game *data, int flag);
void	ft_arrfree(char **arr);
int		ft_error(char *str, int exit);

// testing

void	print_map(char **map, int map_width);
void	display_struct(t_cub *cub);

#endif