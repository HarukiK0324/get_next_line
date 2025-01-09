/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haruki <haruki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:53:16 by haruki            #+#    #+#             */
/*   Updated: 2025/01/09 17:00:44 by haruki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
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

char	*ft_strjoin(char *line, char *buffer)
{
	char	*new_line;
	int		i;
	int		j;

	if (line == NULL)
		return (buffer);
	new_line = (char *)malloc(ft_strlen(line) + ft_strlen(buffer) + 1);
	if (new_line == NULL)
	{
		free(buffer);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (line[i] != '\0')
        new_line[i++] = line[j++];
	free(line);
    j = 0;
	while (buffer[j] != '\0')
        new_line[i++] = buffer[j++];
	free(buffer);
	new_line[i] = '\0';
	return (new_line);
}

char	*get_line_from_buffer(char *line, int *fd)
{
	char	*buffer;
	int		bytes_read;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = read(*fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(buffer);
		if (bytes_read < 0)
			return (NULL);
		*fd = -1;
		return (line);
	}
	buffer[bytes_read] = '\0';
	line = ft_strjoin(line, buffer);
	return (line);
}

char	*get_first_line(char *line)
{
	char	*first_line;
	int		i;

	if (find_newline(line) == -1 || (find_newline(line) + 1) == ft_strlen(line))
		return (line);
	first_line = (char *)malloc(find_newline(line) + 2);
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
	first_line = update_line(first_line, &line);
	return (first_line);
}

char	*update_line(char *first_line, char **line)
{
	int		i;
	int		j;
	char	*new_line;

	i = find_newline(*line) + 1;
    if(i == ft_strlen(*line))
    {
        free(*line);
        *line = NULL;
        return (first_line);
    }
	new_line = (char *)malloc(ft_strlen(*line) - i);
	if (!new_line)
	{
		free(first_line);
		return (NULL);
	}
	j = 0;
	while (*line[i] != '\0')
		new_line[j++] = *line[i++];
	new_line[j] = '\0';
	*line = new_line;
	return (first_line);
}
