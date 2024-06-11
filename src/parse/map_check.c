#include "../../include/cub.h"

int	check_walls(char **map, int map_width);
int	check_line(char **map, int line);
int	check_column(char **map, int col);
int	is_gap(char **map, int line, int col);
int	check_chars(char **map);

int	map_valid(t_cub *cub)
{
	char	**map;

	map = cub->map;
	if (!check_chars(map))
		ft_error("wrong characters in map");
	if (!check_walls(map, cub->map_width))
	{
		print_map(map, cub->map_width);
		ft_error("the walls of the map are not closed");
	}
	return (1);
}

int	check_chars(char **map)
{
	int		player;
	int		i;
	char	*line;

	player = 0;
	i = 0;
	while (map[i])
	{
		line = map[i++];
		if (!is_mapline(line))
			return (0);
		while (*line)
		{
			if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
				player++;
			line++;
		}
	}
	return (player == 1);
}

// for testing
int	check_walls(char **map, int map_width)
{
	int	i;

	i = 0;
	while (map && map[i])
	{
		if (!check_line(map, i))
		{
			printf("error line index %d: %s\n", i, map[i]);
			return (0);
		}
		i++;
	}
	i = 0;
	while (i < map_width)
	{
		if (!check_column(map, i))
		{
			printf("error column index %d\n", i);
			return (0);
		}
		i++;
	}
	return (1);
}

// check if each line has a 1 at end and start and at gaps
int	check_line(char **map, int line)
{
	int		i;
	char	**s;

	if (!map || !map[line])
		return (0);
	s = ft_split(map[line], ' ');
	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i][0] != '1' || s[i][ft_strlen(s[i]) - 1] != '1')
			return (ft_arrfree(s), 0);
		i++;
	}
	return (ft_arrfree(s), 1);
}

// check if each column has a 1 on top and bottom and at gaps
int	check_column(char **map, int col)
{
	int		i;

	if (!map)
		return (0);
	i = 0;
	while (map[i])
	{
		if (is_gap(map, i, col) && i > 0 && !is_gap(map, i - 1, col))
		{
			if (map[i - 1][col] != '1')
				return (0);
		}
		if (is_gap(map, i, col) && map[i + 1] && !is_gap(map, i + 1, col))
		{
			if (map[i + 1][col] != '1')
				return (0);
		}
		i++;
	}
	return (1);
}

int	is_gap(char **map, int line, int col)
{
	return (map[line] && (col >= (int)ft_strlen(map[line]) || map[line][col] == ' '));
}
