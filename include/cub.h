/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:54:12 by sshahary          #+#    #+#             */
/*   Updated: 2024/06/11 17:00:02 by asemsey          ###   ########.fr       */
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

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 980
#define TILE 32
#define FOV 60
#define SPEED 2
#define ROT 0.05

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

//raycasting

int		check_circle(float angle, char c);
int		check_intersect(float angle, float *inter, float *step, int horiflag);
int		wall_hit(float x, float y, t_game *data);
float	nor_angle(float angle);
float	find_h_intersect(t_game *data, float angle);
float	find_v_intersect(t_game *data, float angle);
void	ray_cast(t_game *data);

//rendering

void	pixel_put(t_game *data, int x, int y, int color);
void	draw_floor_ceiling(t_game *data, int ray, int t_pix, int b_pix);
void	get_color(t_game *data);
void	render(t_game *data, int ray);

// controlling

void 	key(mlx_key_data_t keydata, void *param);
void	release(t_game *data, mlx_key_data_t keydata);
void	move(t_game *data, t_point far_pos, t_point new_pos);
void	rotate(t_game *data, int i);
void	control(t_game *data);

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

int		ft_arrlen(char **arr);
void	ft_arrfree(char **arr);
char	**ft_arrdup(char **arr);

// testing

void	print_map(char **map, int map_width);
void	display_struct(t_cub *cub);
void	ft_free(t_game *data);
void	ft_error(char *str);

#endif