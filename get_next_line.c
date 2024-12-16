/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haruki <haruki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:53:20 by haruki            #+#    #+#             */
/*   Updated: 2024/12/16 11:35:04 by haruki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line_from_buffer(char *line, int fd)
{
	char	*buffer;
	int		result;

	buffer = (char *)malloc(BUFFER_SIZE);
	if (buffer == NULL)
		return (NULL);
	result = read(fd, buffer, BUFFER_SIZE);
	if (result < 0)
	{
		free(buffer);
		return (NULL);
	}
	else if (result == 0)
	{
		free(buffer);
		return (0);
	}
	line = ft_strjoin(line, buffer);
	free(buffer);
	if (line == NULL)
		return (NULL);
	return (line);
}

int	find_newline(char *line)
{
	int	i;

	if (line == NULL)
		return (-1);
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*last_line(char *line)
{
	int		i;
	char	*last_line;

	i = 0;
	while (line[i] != '\0')
		i++;
	last_line = (char *)malloc(sizeof(char) * (i + 1));
	if (last_line == NULL)
		return (NULL);
	i = 0;
	while (line[i] != '\0')
	{
		last_line[i] = line[i];
		i++;
	}
	last_line[i] = '\0';
	return (last_line);
}

char	*first_line(char *line)
{
	int		i;
	char	*first_line;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0' || (line[i] == '\n' && line[i + 1] == '\0'))
		return (last_line(line));
	first_line = (char *)malloc(sizeof(char) * (i + 2));
	if (first_line == NULL)
		return (NULL);
	i = 0;
	while (line[i] != '\n')
	{
		first_line[i] = line[i];
		i++;
	}
	first_line[i] = '\n';
	first_line[i + 1] = '\0';
	line = &line[i + 1];
	return (first_line);
}

char	*get_next_line(int fd)
{
	static char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (find_newline(line) == -1)
	{
		line = get_line_from_buffer(line, fd);
		if (line == NULL)
			return (NULL);
		else if (line == 0)
			break ;
	}
	return (first_line(line));
}
#include <stdio.h>

int	main(void)
{
	char	*s;

	s = get_next_line(1);
	printf("%s\n", s);
	return (0);
}
