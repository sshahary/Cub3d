/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:31:27 by asemsey           #+#    #+#             */
/*   Updated: 2024/05/27 12:12:03 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

char	*read_variables(t_cub *cub, int fd);
char	*read_map(t_cub *cub, char *last_line, int fd);
int		map_length(char *filename);
int		is_identifier(char *str);
void	get_identifier(char *line, t_cub *cub);
int		is_rgb(char *str, int iter);
void	set_rgb(char *str, t_rgb *rgb);
int		is_mapline(char *str);
int		is_mapchar(char c);
int		ft_isspace(char c);
void	set_mapsize(t_cub *cub);

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
	print_map(cub->map);
	if (line)
		return (0);
	set_mapsize(cub);
	close(fd);
	return (1);
}

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

void	set_mapsize(t_cub *cub)
{
	int		i;
	int		max_len;

	if (!cub->map)
		return ;
	i = 0;
	max_len = 0;
	while (cub->map[i])
	{
		if ((int)ft_strlen(cub->map[i]) > max_len)
			max_len = (int)ft_strlen(cub->map[i]);
		i++;
	}
	cub->map_length = i;
	cub->map_width = max_len;
}

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

void	set_rgb(char *str, t_rgb *rgb)
{
	if (!is_rgb(str, 0))
		return ;
	rgb->r = ft_atoi(str);
	while (ft_isdigit(*str))
		str++;
	rgb->g = ft_atoi(++str);
	while (ft_isdigit(*str))
		str++;
	rgb->b = ft_atoi(++str);
}

// is str in rgb format (recursive, set iter to 0)
int	is_rgb(char *str, int iter)
{
	int	i;

	i = 0;
	while (*str && ft_isdigit(*str))
	{
		i++;
		str++;
	}
	if (i > 3 || !i)
		return (0);
	if (iter < 2 && *str++ != ',')
		return (0);
	if (iter >= 2 && !*str)
		return (1);
	return (is_rgb(str, ++iter));
}

void	get_identifier(char *line, t_cub *cub)
{
	char	*filename;
	
	filename = line + 2;
	while (*filename && *filename == ' ')
		filename++;
	if (!*filename)
		return ;
	if (!ft_strncmp(line, "NO ", 3))
		cub->no_png = filename;
	else if (!ft_strncmp(line, "SO ", 3))
		cub->so_png = filename;
	else if (!ft_strncmp(line, "EA ", 3))
		cub->ea_png = filename;
	else if (!ft_strncmp(line, "WE ", 3))
		cub->we_png = filename;
	else if (!ft_strncmp(line, "F ", 2))
		set_rgb(filename, &(cub->f_rgb));
	else if (!ft_strncmp(line, "C ", 2))
		set_rgb(filename, &(cub->c_rgb));
}

int	is_mapline(char *str)
{
	int	i;
	int	mapchars;

	i = 0;
	mapchars = 0;
	while (str && *str)
	{
		if (i > 0 && (*str == '\n' && !*(str + 1)))
			break ;
		if (is_mapchar(*str))
			mapchars++;
		if (!ft_isspace(*str) && !is_mapchar(*str))
			return (0);
		i++;
		str++;
	}
	if (!mapchars)
		return (0);
	return (1);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t');
}

// "0 for an empty space, 1 for a wall, and N,S,E or W"
int	is_mapchar(char c)
{
	return (c == '0' || c == '1'
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

// NOrth SOuth EAst WEst Floor Ceiling
int	is_identifier(char *str)
{
	return (!ft_strncmp(str, "NO ", 3)
		|| !ft_strncmp(str, "SO ", 3)
		|| !ft_strncmp(str, "EA ", 3)
		|| !ft_strncmp(str, "WE ", 3)
		|| !ft_strncmp(str, "F ", 2)
		|| !ft_strncmp(str, "C ", 2));
}

// // test is_rgb
// int main(int argc, char const *argv[])
// {
// 	char *str = "1,12,8 ";
// 	printf("%d\n", is_rgb(str, 0));
// 	return 0;
// }
