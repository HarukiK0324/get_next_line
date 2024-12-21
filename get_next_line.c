/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haruki <haruki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:53:20 by haruki            #+#    #+#             */
/*   Updated: 2024/12/21 19:46:49 by haruki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int ft_strlen(char *s)
{
	int i;

	i = 0;
	if(s == NULL)
		return (0);
	while(s[i] != '\0')
		i++;
	return i;
}

int find_newline(char *line)
{
	int i;

	i  = 0;
	if(line == NULL)
		return (-1);
	while (line[i] != '\0')
	{
		if (line[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char *buffer;
	int result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (find_newline(line) == -1)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (buffer == NULL)
			return (NULL);
		result = read(fd, buffer, BUFFER_SIZE);
		if (result == -1)
		{
			free(buffer);
			return (NULL);
		}
		else if (result == 0)
		{
			if (line == NULL || line[0] == '\0')
			{
				free(buffer);
				return (NULL);
			}
			break;
		}
		buffer[result] = '\0';
		char *tmp = malloc(ft_strlen(line) + ft_strlen(buffer) + 1);
		if (tmp == NULL)
		{
			free(buffer);
			return (NULL);
		}
		int i = 0, j = 0;
		while (line != NULL && line[i] != '\0')
		{
			tmp[i] = line[i];
			i++;
		}
		while (buffer[j] != '\0')
		{
			tmp[i] = buffer[j];
			i++;
			j++;
		}
		tmp[i] = '\0';
		free(line);
		free(buffer);
		line = tmp;
	}
	if (find_newline(line) == -1)
	{
		if (line == NULL || line[0] == '\0')
			return (NULL);
		return (line);
	}
	int newline_index = find_newline(line);
	char *tmp = malloc(newline_index + 2);
	if (tmp == NULL)
		return (NULL);
	int i = 0;
	while (line[i] != '\n')
	{
		tmp[i] = line[i];
		i++;
	}
	tmp[i] = '\n';
	i++;
	tmp[i] = '\0';
	char *tmp2 = malloc(ft_strlen(line) - i + 1);
	if (tmp2 == NULL)
	{
		free(tmp);
		return (NULL);
	}
	int j = 0;
	while (line[i] != '\0')
	{
		tmp2[j] = line[i];
		i++;
		j++;
	}
	tmp2[j] = '\0';
	free(line);
	line = tmp2;
	return (tmp);
}
