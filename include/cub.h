/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:54:12 by sshahary          #+#    #+#             */
/*   Updated: 2024/05/26 15:38:49 by sshahary         ###   ########.fr       */
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

#define WIDTH 5120
#define HEIGHT 2880
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 980
#define TILE 30
#define FOV 60


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
typedef struct s_cub
{
	char	**maps;
	int		x;
	int		y;
	int		wid;
	int		height;
}	t_cub;


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

#endif
