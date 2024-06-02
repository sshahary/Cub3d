#include "../../include/cub.h"

int	check_walls(char **map, int map_width);
int	check_top_bottom(char **map, int line);
int	check_line(char **map, int line);
int	check_column(char **map, int col);
int	only_char(char *str, char c);
int is_gap(char **map, int line, int col);
int	check_lr(char **map, int col);

int	map_valid(t_cub *cub)
{
	// t_point	start;
	char	**map;

	// map = ft_arrdup(cub->map);
	map = cub->map;
	// start.x = 0;
	// start.y = 0;
	// while (map[start.y][start.x] && map[start.y][start.x] != '1')
	// 	start.x++;
	if (!check_walls(map, cub->map_width))
	{
		print_map(map);
		ft_error("the walls of the map are not closed");
	}
	// ft_arrfree(map);
	return (1);
}

int	check_walls(char **map, int map_width)
{
	int	i;

	i = 0;
	// check first and last if only 1
	// check if each line has a 1 at end and start
	// also check they are connected to another 1
	// check if each column has a 1 on top and bottom
	// also check next to gaps everywhere!
	// needed fts:
		// check column
		// check line
		// check top bottom
		// check left right
	while (map && map[i])
	{
		if ((i == 0 || !map[i + 1]) && !check_top_bottom(map, i))
			return (0);
		else if (!check_line(map, i))
			return (0);
		printf("line: %s--- index %d ok\n", map[i], i);
		i++;
	}
	i = 0;
	while (i < map_width)
	{
		if ((i == 0 || i == map_width - 1) && !check_lr(map, i))
			return (0);
		if (!check_column(map, i))
			return (0);
		printf("column index %d ok\n", i);
		i++;
	}
	
	return (1);
}

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

int	check_column(char **map, int col)
{
	int		i;

	if (!map)
		return (0);
	i = 0;
	while (map[i])
	{
		if ((i == 0 || !map[i + 1]) && col < (int)ft_strlen(map[i]) && map[i][col] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	check_top_bottom(char **map, int line)
{
	int		i;
	char	**s;

	if (!map || !map[line])
		return (0);
	i = 0;
	s = ft_split(map[line], ' ');
	if (!s)
		return (0);
	while (s[i])
	{
		if (!only_char(s[i], '1'))
			return (ft_arrfree(s), 0);
		i++;
	}
	return (ft_arrfree(s), 1);
}

int	check_lr(char **map, int col)
{
	int		i;

	if (!map)
		return (0);
	i = 0;
	while (map[i])
	{
		if (!is_gap(map, i, col) && map[i][col] != '1')
			return (0);
		i++;
	}
	return (1);
}

int is_gap(char **map, int line, int col)
{
	return ((map[line] && (col >= (int)ft_strlen(map[line]) || map[line][col] == ' ')) || !map[line]);
}

int	only_char(char *str, char c)
{
	while (str && *str)
	{
		if (*str != c)
			return (0);
		str++;
	}
	return (1);
}
