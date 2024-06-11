/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:55:15 by asemsey           #+#    #+#             */
/*   Updated: 2024/06/11 17:00:13 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	is_mapchar(char c);
int	is_mapline(char *str);
int	is_identifier(char *str);
int	is_rgb(char *str, int iter);

// "0 for an empty space, 1 for a wall, and N,S,E or W"
int	is_mapchar(char c)
{
	return (c == '0' || c == '1'
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

// 1 if line only has mapchars
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
		if (*str != ' ' && !is_mapchar(*str))
			return (0);
		i++;
		str++;
	}
	if (!mapchars)
		return (0);
	return (1);
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
	if (iter >= 2 && (!*str || *str == '\n'))
		return (1);
	return (is_rgb(str, ++iter));
}

int	cub_filename(char *str)
{
	char	*tmp;

	tmp = ft_strrchr(str, '.');
	if (!tmp)
		return (0);
	if (ft_strncmp(tmp, ".cub", ft_strlen(tmp)))
		return (0);
	return (1);
}
