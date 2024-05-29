/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:02:24 by asemsey           #+#    #+#             */
/*   Updated: 2024/05/29 11:46:31 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	check_walls(char **map, t_point start);

// there are already no other chars or empty lines,
// all that needs checking is the shape.
int	map_valid(t_cub *cub)
{
	t_point	start;
	char	**map;

	map = cub->map;
	// start is top left corner
	start.x = 0;
	start.y = 0;
	// go right until there is a wall
	while (map[start.y][start.x] && map[start.y][start.x] != '1')
		start.x++;
	if (!check_walls(map, start))
		ft_error("the walls of the map are not closed");
	printf("ok1\n");
	return (1);
}

static int	turn(int dir, char l_r)
{
	if (l_r == 'r')
	{
		if (++dir > 3)
			dir = 0;
	}
	if (l_r == 'l')
	{
		if (--dir < 0)
			dir = 3;
	}
	return (dir);
}

static int	step(char **map, int dir, t_point *p)
{
	if (dir == 0 && map[p->y][p->x + 1])
	{
		p->x++;
		return (1);
	}
	if (dir == 1 && map[p->y])
	{
		p->y++;
		return (1);
	}
	if (dir == 2 && p->x > 0)
	{
		p->x--;
		return (1);
	}
	if (dir == 3 && p->y > 0)
	{
		p->y--;
		return (1);
	}
	return (0);
}

// dir for left is: turn(dir, 'l')
static char	dir_char(char **map, int dir, t_point p)
{
	if (dir == 0)
		return (map[p.y][p.x + 1]);
	if (dir == 1 && map[p.y])
		return (map[p.y + 1][p.x]);
	if (dir == 2 && p.x > 0)
		return (map[p.y][p.x - 1]);
	if (dir == 3 && p.y > 0)
		return (map[p.y - 1][p.x]);
	return (0);
}

// dir:
// 		right	0
// 		down	1
// 		left	2
// 		up		3

int	check_walls(char **map, t_point start)
{
	t_point	p;
	int		dir;

	p.x = start.x;
	p.y = start.y;
	dir = 0;
	print_map(map);
	while (1)
	{// follow the walls and stay left
		// if left is 1 turn left
		// elif straight is 1 do nothing
		// elif right is 1 turn right
		// else turn back / fail
		// walk once and go again
		printf("ok2 %d\n", dir);
		if (dir_char(map, turn(dir, 'l'), p) == '1')
			dir = turn(dir, 'l');
		else if (dir_char(map, dir, p) == '1')
			;
		else if (dir_char(map, turn(dir, 'r'), p) == '1')
			dir = turn(dir, 'r');
		else
			dir = turn(turn(dir, 'r'), 'r');
		if (!step(map, dir, &p))
			return (0);
		if (p.x == start.x && p.y == start.y)
			break ;// if you reach the start its correct
	}
	return (1);
}
