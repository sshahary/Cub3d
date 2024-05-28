/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubdata.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:29:32 by asemsey           #+#    #+#             */
/*   Updated: 2024/05/28 20:21:47 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBDATA_H
# define CUBDATA_H

# include "cub.h"

typedef struct s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_rgb;

typedef struct s_cub
{
	char	**map;
	char	*no_png;
	char	*so_png;
	char	*ea_png;
	char	*we_png;
	t_rgb	c_rgb;
	t_rgb	f_rgb;
	int		map_length;
	int		map_width;
	int		x;
	int		y;
}	t_cub;

#endif