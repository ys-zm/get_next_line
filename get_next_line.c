/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/08 12:19:49 by yzaim         #+#    #+#                 */
/*   Updated: 2022/11/14 13:00:26 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <limits.h>

size_t	check_pos_nl(char *buf)
{
	size_t	i;

	i = 0;
	while (buf && buf[i] != '\n' && buf[i] != '\0')
		i++;
	if (buf[i] == '\n')
		i++;
	return (i);
}

size_t	check_char(char c, char *str)
{
	while (str && *str++)
	{
		if (*str == c)
			return (1);
	}
	return (0);
}

char	*cut_store(char *store, size_t pos, size_t store_len)
{
	char *str;

	str = ft_strdup_gnl(store, pos, store_len);
	free(store);
	store = NULL;
	return (str);
}

char	*ft_free_null(char **line, char **rem, char **buf)
{
	free(*line);
	free(*rem);
	free(*buf);
	*line = NULL;
	*rem = NULL;
	*buf = NULL;
	return (NULL);
}

char	*append_buf(int fd, char *store, char *buf)
{
	ssize_t	read_ret;
	
	read_ret = 1;
	while (read_ret)
	{
		read_ret = read(fd, buf, BUFFER_SIZE); 
		if (read_ret == -1)
			return (NULL);
		buf[read_ret] = '\0';
		store = ft_strjoin_gnl(store, buf);
		if (!store)
			return (NULL);
		if (store && check_char('\n', store))
			return (store);
	}
	return (store);	
}

char	*find_line(char **store)
{
	size_t	pos;
	size_t	store_len;
	char	*line;

	line = NULL;
	
	if (store && *store && check_char('\n', *store))
	{
		pos = check_pos_nl(*store);
		store_len = ft_strlen(*store);
		line = ft_strdup_gnl(*store, 0, pos);
		if (line == NULL)
		{
			free(*store);
			return (line);
		}
		*store = cut_store(*store, pos, store_len);
	}
	else if (store && *store)
	{
		line = ft_strjoin_gnl(line, *store);
		free(*store);
		*store = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*store = NULL;
	char		*line;
	char		*buf;

	line = NULL;
	if (read(fd, NULL, 0) == -1 || BUFFER_SIZE < 1 || BUFFER_SIZE > 2147483647)
		return (NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	buf[BUFFER_SIZE] = '\0';		
	store = append_buf(fd, store, buf);
	if (!store)
	{
		// ft_free_null(&line, &store, &buf);
		free(store);
		free(buf);
		return (NULL);
	}
	if (store && *store)
		line = find_line(&store);
	if (!line)
	{
		//ft_free_null(&line, &store, &buf);
		free(store);
		free(buf);
		free(line);
		return (NULL);
	}
	if (buf)
		free(buf);
	return (line);
}

// int	main(void)
// {
// 	int	fd;
// 	int	i;
// 	char *line;
	
// 	fd = open("file", O_RDONLY);
// 	i = 0;

// 	while (i++ < 19)
// 	{
// 	line = get_next_line(fd);
// 	printf("%s\n", line);
// 	}
	
// 	close(fd);
// }
