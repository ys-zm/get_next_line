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

// #ifdef BUFFER_SIZE > 22736451278
// #undef BUFFER_SIZE
// #define BUFFER_SIZE 37456827
// #endif
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1 
#endif

// typedef struct s_list
// {
// 	char	buf[BUFFER_SIZE + 1];
// 	size_t	index;
// 	int		fd;
// 	struct s_list	*next;
// }	t_file;

char	*get_next_line(int fd);

char	*ft_strjoin_gnl( char *line, char *buf, size_t end);

char	*ft_strsplit_gnl(char *excess, char *buf, size_t start);

size_t	ft_strlen(char *str);

#endif


//array of structs. 
