/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:04:14 by asemsey           #+#    #+#             */
/*   Updated: 2024/05/29 11:47:47 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int		read_mapfile(char *filename, t_cub *cub);
int		map_length(char *filename);
char	*read_map(t_cub *cub, char *last_line, int fd);
char	*read_variables(t_cub *cub, int fd);

// main parsing function
int	read_mapfile(char *filename, t_cub *cub)
{
	int		fd;
	int		map_len;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	line = read_variables(cub, fd);
	if (!line)
		return (0);
	map_len = map_length(filename);
	if (!map_len)
		return (0);
	cub->map = (char **)malloc(sizeof(char *) * (map_len + 1));
	if (!cub->map)
		return (0);
	line = read_map(cub, line, fd);
	if (line)
		return (0);
	// if (line || !map_valid(cub))
	// 	return (0);
	set_mapsize(cub);
	close(fd);
	return (1);
}

// read the map part of the file
char	*read_map(t_cub *cub, char *last_line, int fd)
{
	char	*line;
	int		i;

	i = 0;
	if (last_line && *last_line && is_mapline(last_line))
		cub->map[i++] = last_line;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			cub->map[i++] = NULL;
			return (NULL);
		}
		if (!*line || !is_mapline(line))
		{
			cub->map[i++] = NULL;
			return (line);
		}
		cub->map[i++] = line;
	}
}

// read the colors and texture files out of the file
char	*read_variables(t_cub *cub, int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (NULL);
		if (*line != '\n' && !is_identifier(line))
			return (line);
		get_identifier(line, cub);
	}
}

// count the map lines to allocate
int		map_length(char *filename)
{
	int		fd;
	int		in_map;
	int		count;
	char	*line = NULL;

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
			break;
		free(line);
		if (in_map)
			count++;
	}
	free(line);
	return (close(fd), count);
}
