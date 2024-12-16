/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haruki <haruki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:53:16 by haruki            #+#    #+#             */
/*   Updated: 2024/12/13 13:53:19 by haruki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t ft_strlen(char *s)
{
    size_t len = 0;
    while (s[len] != '\0')
        len++;
    return (len);
}

char *ft_strjoin(char *s1,char *s2)
{
    char *ptr;
    size_t i;
    size_t index;

    i = 0;
    ptr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    if (ptr == NULL)
        return NULL;
    while (s1[i] != '\0')
    {
        ptr[i] = s1[i];
        i++;
    }
    index = 0;
    while (s2[index] != '\0')
    {
        ptr[i] = s2[index];
        i++;
        index++;
    }
    ptr[i] = '\0';
    free(s1);
    return ptr;
}
