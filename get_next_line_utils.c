/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haruki <haruki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:53:16 by haruki            #+#    #+#             */
/*   Updated: 2024/12/21 18:24:28 by haruki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *s)
{
	int	len = 0;

	if (s == NULL)
		return (0);
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	int		i = 0, j = 0;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (result == NULL)
		return (NULL);
	if (s1 != NULL)
		while (s1[i] != '\0')
		{
			result[i] = s1[i];
			i++;
		}
	if (s2 != NULL)
		while (s2[j] != '\0')
			result[i++] = s2[j++];
	result[i] = '\0';
	free(s1);
	return (result);
}
