/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkasamat <hkasamat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:53:20 by haruki            #+#    #+#             */
/*   Updated: 2025/01/09 20:13:17 by hkasamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*line;
	char		*first_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (find_newline(line) == -1)
	{
		line = get_line_from_buffer(line, &fd);
		if (!line)
			return (NULL);
		else if (fd == -1)
			break ;
	}
	first_line = get_first_line(line);
	line = update_line(line, &first_line);
	return (first_line);
}
