/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:31:00 by asemsey           #+#    #+#             */
/*   Updated: 2024/05/22 13:11:35 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	gnl_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i] != '\0')
		i++;
	return (i);
}

static int	length(const char *s, unsigned int start, size_t len)
{
	if (len > gnl_strlen(s) - start)
		return (gnl_strlen(s) - start);
	return (len);
}

char	*gnl_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (s[0] == '\0' || len == 0 || start >= gnl_strlen(s))
	{
		str = (char *)malloc(1);
		if (str == 0)
			return (0);
		str[0] = '\0';
		return (str);
	}
	len = length(s, start, len);
	str = (char *)malloc(len + 1);
	if (str == 0)
		return (0);
	while (i < len && (start + i) < gnl_strlen(s))
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*gnl_strjoin(char *s1, const char *s2)
{
	char	*s;
	size_t	i;
	size_t	j;

	i = 0;
	s = (char *)malloc(gnl_strlen(s1) + gnl_strlen(s2) + 1);
	if (!s || (!s1 && !s2))
		return (NULL);
	while (s1 && s1[i] != '\0')
	{
		s[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j] != '\0')
	{
		s[i + j] = s2[j];
		j++;
	}
	s[i + j] = '\0';
	if (s1)
		free(s1);
	return (s);
}

char	*gnl_strchr(char *s, int c)
{
	int	i;

	i = 0;
	c = (char)c;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	if (s[i] == c)
		return (&s[i]);
	return (0);
}
