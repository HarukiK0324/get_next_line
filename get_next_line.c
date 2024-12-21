/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haruki <haruki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:53:20 by haruki            #+#    #+#             */
/*   Updated: 2024/12/21 18:23:42 by haruki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line_from_buffer(char *line, int *fd)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	bytes_read = read(*fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(buffer);
		if (bytes_read == 0)
			*fd = -1;
		return (line);
	}
	buffer[bytes_read] = '\0';
	line = ft_strjoin(line, buffer);
	free(buffer);
	return (line);
}

int	find_newline(char *line)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (-1);
	while (line[i] != '\0')
	{
		if (line[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_first_line(char *line)
{
	int		i;
	char	*first_line;

	i = 0;
	if (line == NULL || line[0] == '\0')
		return (NULL);
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	first_line = malloc(i + 1);
	if (first_line == NULL)
		return (NULL);
	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		first_line[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
		first_line[i++] = '\n';
	first_line[i] = '\0';
	return (first_line);
}

char	*update_line(char *line)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	j = 0;
	if (line == NULL || line[0] == '\0')
		return (NULL);
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0')
	{
		free(line);
		return (NULL);
	}
	i++;
	new_line = malloc(ft_strlen(line) - i + 1);
	if (new_line == NULL)
		return (NULL);
	while (line[i])
		new_line[j++] = line[i++];
	new_line[j] = '\0';
	free(line);
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*first_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (find_newline(line) == -1)
	{
		line = get_line_from_buffer(line, &fd);
		if (line == NULL)
			return (NULL);
		if (fd == -1)
			break ;
	}
	first_line = get_first_line(line);
	line = update_line(line);
	return (first_line);
}
