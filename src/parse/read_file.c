/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:04:14 by asemsey           #+#    #+#             */
/*   Updated: 2024/06/12 10:58:30 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int		read_mapfile(char *filename, t_cub *cub);
int		map_length(char *filename);
char	*read_map(t_cub *cub, char *last_line, int fd);
char	*read_variables(t_cub *cub, int fd);
void	trim_newlines(t_cub *cub);

// main parsing function
int	read_mapfile(char *filename, t_cub *cub)
{
	int		fd;
	int		map_len;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_error("failed to open file", 0));
	line = read_variables(cub, fd);
	if (!line)
		return (ft_error("texture files and colors incorrect", 0));
	map_len = map_length(filename);
	if (!map_len)
		return (free(line), ft_error("could not read map", 0));
	cub->map = (char **)malloc(sizeof(char *) * (map_len + 1));
	if (!cub->map)
		return (free(line), ft_error("failed to allocate memory", 0));
	line = read_map(cub, line, fd);
	close(fd);
	trim_newlines(cub);
	if (line)
		return (free(line), ft_error("invalid line in map", 0));
	set_coordinates(cub);
	if (!map_valid(cub))
		return (0);
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
	return (NULL);
}

// read the colors and texture files out of the file
char	*read_variables(t_cub *cub, int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (close(fd), NULL);
		if (*line != '\n' && !is_identifier(line))
			break ;
		get_identifier(line, cub);
		free(line);
	}
	if (!cub->ea_png || !cub->no_png || !cub->so_png || !cub->we_png
		|| cub->c_rgb == -1 || cub->f_rgb == -1)
		return (close(fd), free(line), NULL);
	return (line);
}

static void	ft_nullterminate(t_cub *cub)
{
	char	*str;

	str = cub->no_png;
	while (str && *str && *str != '\n')
		str++;
	*str = '\0';
	str = cub->ea_png;
	while (str && *str && *str != '\n')
		str++;
	*str = '\0';
	str = cub->so_png;
	while (str && *str && *str != '\n')
		str++;
	*str = '\0';
	str = cub->we_png;
	while (str && *str && *str != '\n')
		str++;
	*str = '\0';
}

void	trim_newlines(t_cub *cub)
{
	int		i;
	char	*str;

	i = 0;
	while (cub->map && cub->map[i])
	{
		str = cub->map[i++];
		while (*str)
		{
			if (*str == '\n')
				*str = '\0';
			str++;
		}
	}
	ft_nullterminate(cub);
}
