/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haruki <haruki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:53:20 by haruki            #+#    #+#             */
/*   Updated: 2024/12/17 11:58:24 by haruki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line_from_buffer(char *line, int fd)
{
	char	*buffer;
	int		result;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	result = read(fd, buffer, BUFFER_SIZE);
	buffer[result] = '\0';
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

char	*get_first_line(char *line)
{
	int		i;
	char	*first_line;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (line);
	else if ((line[i] == '\n' && line[i + 1] == '\0'))
		return (line);
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
	return (first_line);
}

char	*update_line(char *line)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] != '\n')
		i++;
	i++;
	new_line = (char *)malloc(ft_strlen(line) - i + 1);
	if (new_line == NULL)
		return (NULL);
	while (line[i] != '\0')
	{
		new_line[j] = line[i];
		i++;
		j++;
	}
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
		line = get_line_from_buffer(line, fd);
		if (line == NULL)
			return (NULL);
		else if (line == 0)
			break ;
	}
	first_line = get_first_line(line);
	if (ft_strlen(first_line) == ft_strlen(line))
	{
		free(line);
		line = NULL;
	}
	else
		line = update_line(line);
	return (first_line);
}
