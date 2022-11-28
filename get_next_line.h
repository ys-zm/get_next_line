/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/08 12:20:43 by yzaim         #+#    #+#                 */
/*   Updated: 2022/11/11 14:49:50 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
    #define GET_NEXT_LINE_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>

// #ifdef BUFFER_SIZE > MAX_INT - 1
// #undef BUFFER_SIZE
// #define BUFFER_SIZE MAX_INT - 1
// #endif
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 100000
#endif

char	*get_next_line(int fd);

char	*ft_strjoin_gnl(char *line, char *buf);

char	*ft_strdup_gnl(char *str, size_t start, size_t end);

size_t	ft_strlen(char *str);

char	*ft_free_null(char **line, char **rem, char **buf);

#endif
