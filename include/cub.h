/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:54:12 by sshahary          #+#    #+#             */
/*   Updated: 2024/05/27 11:57:28 by asemsey          ###   ########.fr       */
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

// parse

int		read_mapfile(char *filename, t_cub *cub);
char	*read_variables(t_cub *cub, int fd);
int		is_identifier(char *str);
void	get_identifier(char *line, t_cub *cub);
int		is_rgb(char *str, int iter);
void	set_rgb(char *str, t_rgb *rgb);
int		is_mapline(char *str);
int		is_mapchar(char c);
void	set_mapsize(t_cub *cub);

void	print_map(char **map);

#endif