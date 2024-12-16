/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haruki <haruki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:53:13 by haruki            #+#    #+#             */
/*   Updated: 2024/12/13 13:53:37 by haruki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

char *get_next_line(int fd);
size_t ft_strlen(char *s);
char *ft_strjoin(char *s1,char *s2);

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

#endif