/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:21:59 by asemsey           #+#    #+#             */
/*   Updated: 2024/06/12 09:35:44 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	ft_error(char *str, int exit)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(str, 2);
	return (exit);
}

int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

char	**ft_arrdup(char **arr)
{
	char	**dup;
	int		i;

	if (!arr || !arr[0])
		return (NULL);
	dup = (char **)malloc(sizeof(char *) * (ft_arrlen(arr) + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		dup[i] = ft_strdup(arr[i]);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

void	ft_arrfree(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	free(arr);
}
