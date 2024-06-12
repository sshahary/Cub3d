/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:31:27 by asemsey           #+#    #+#             */
/*   Updated: 2024/06/12 10:55:48 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	get_identifier(char *line, t_cub *cub);
int		get_rgb(char *str);
void	set_coordinates(t_cub *cub);

// set player_dir and coordinates
void	set_player(t_cub *cub, int y)
{
	int		i;
	char	c;

	i = 0;
	c = 0;
	cub->y = y;
	while (cub->map[y][i] && !c)
	{
		if (cub->map[y][i] == 'E' || cub->map[y][i] == 'S'
			|| cub->map[y][i] == 'W' || cub->map[y][i] == 'N')
		{
			c = cub->map[y][i];
			cub->x = i;
		}
		i++;
	}
	if (c == 'E')
		cub->player_dir = 0;
	if (c == 'S')
		cub->player_dir = 1;
	if (c == 'W')
		cub->player_dir = 2;
	if (c == 'N')
		cub->player_dir = 3;
}

// map width and length, player coordinates
void	set_coordinates(t_cub *cub)
{
	int		i;
	int		max_len;

	if (!cub->map)
		return ;
	i = 0;
	max_len = 0;
	while (cub->map[i])
	{
		if (ft_strchr(cub->map[i], 'N') || ft_strchr(cub->map[i], 'S')
			|| ft_strchr(cub->map[i], 'E') || ft_strchr(cub->map[i], 'W'))
			set_player(cub, i);
		if ((int)ft_strlen(cub->map[i]) > max_len)
			max_len = (int)ft_strlen(cub->map[i]);
		i++;
	}
	cub->map_length = i;
	cub->map_width = max_len;
}

// turn rgb string to encoded value
int	get_rgb(char *str)
{
	int	r;
	int	g;
	int	b;

	if (!is_rgb(str, 0))
		return (0);
	r = ft_atoi(str);
	while (ft_isdigit(*str))
		str++;
	g = ft_atoi(++str);
	while (ft_isdigit(*str))
		str++;
	b = ft_atoi(++str);
	if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0)
		return (-1);
	return (r << 24 | g << 16 | b << 8 | 255);
}

// get the content of a texture/color line
void	get_identifier(char *line, t_cub *cub)
{
	char	*filename;

	if (ft_strlen(line) < 3)
		return ;
	filename = line + 2;
	while (*filename && *filename == ' ')
		filename++;
	if (!*filename || *filename == '\n')
		return ;
	if (!ft_strncmp(line, "NO ", 3))
		cub->no_png = ft_strdup(filename);
	else if (!ft_strncmp(line, "SO ", 3))
		cub->so_png = ft_strdup(filename);
	else if (!ft_strncmp(line, "EA ", 3))
		cub->ea_png = ft_strdup(filename);
	else if (!ft_strncmp(line, "WE ", 3))
		cub->we_png = ft_strdup(filename);
	else if (!ft_strncmp(line, "F ", 2))
		cub->f_rgb = get_rgb(filename);
	else if (!ft_strncmp(line, "C ", 2))
		cub->c_rgb = get_rgb(filename);
}

// count the map lines to allocate
int	map_length(char *filename)
{
	int		fd;
	int		in_map;
	int		count;
	char	*line;

	fd = open(filename, O_RDONLY);
	count = 0;
	in_map = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (close(fd), count);
		if (!in_map && (!is_identifier(line) && *line != '\n'))
			in_map = 1;
		if (in_map && (!is_mapline(line)))
			break ;
		free(line);
		if (in_map)
			count++;
	}
	free(line);
	return (close(fd), count);
}
