/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:54:12 by sshahary          #+#    #+#             */
/*   Updated: 2024/05/29 10:27:16 by asemsey          ###   ########.fr       */
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
# include "cubdata.h"

#define WIDTH 5120
#define HEIGHT 2880
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 980
#define TILE 30
#define FOV 60
#define SPEED 4
#define ROT 0.045


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
	int		wallflag;
}	t_ray;

//data structure for 2dmap
// typedef struct s_cub2
// {
// 	char	**maps;
// 	int		x;
// 	int		y;
// 	int		wid;
// 	int		height;
// }	t_cub2;
// please rename -anna

// main structure
typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_texture_t	*texture;
	t_cub			*cub;
	t_ray			*ray;
	t_player		*player;
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
int		get_color(t_game *data, int flag);
void	draw_wall(t_game *data, int ray, int t_pix, int b_pix);
void	render(t_game *data, int ray);

// controlling

void 	key(mlx_key_data_t keydata, void *param);
void	release(t_game *data, mlx_key_data_t keydata);
void	move(t_game *data, double movex, double movey);
void	rotate(t_game *data, int i);
void	control(t_game *data, double movex, double movey);

// parse

int		read_mapfile(char *filename, t_cub *cub);
int		map_length(char *filename);
void	get_identifier(char *line, t_cub *cub);
void	set_mapsize(t_cub *cub);
int		ft_isspace(char c);
int		is_mapline(char *str);
int		is_identifier(char *str);
int		is_rgb(char *str, int iter);
// int		is_mapchar(char c);

void	print_map(char **map);
void	ft_free(t_game *data);

#endif
