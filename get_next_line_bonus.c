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

#include "get_next_line_bonus.h"
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
	while (str && *str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

char	*cut_store(char **store, size_t pos, size_t store_len)
{
	char *str;

	str = ft_strdup_gnl(*store, pos, store_len);
	free(*store);
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

// size_t	test_read(int fd, char *buf, int buf_size)
// {
// 	static int calls;
// 	int ret;

// 	ret = read(fd, buf, buf_size);
// 	calls++;
// 	if (calls >= 2)
// 		return (-1);
// 	return (ret);
// }

ssize_t	append_buf(int fd, char **store, char *buf)
{
	ssize_t	read_ret;
	
	read_ret = 1;
	
	while (read_ret)
	{
		read_ret = read(fd, buf, BUFFER_SIZE); 
		if (read_ret < 0)
			return (-1);
		if (read_ret == 0)
			return (0);
		buf[read_ret] = '\0';
		if (read_ret > 0)
			*store = ft_strjoin_gnl(*store, buf);
		if (!*store)
			return (-1);
		if (store && check_char('\n', *store))
			return (0);
	}
	return (0);	
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
		*store = cut_store(store, pos, store_len);
	}
	else 
	{
		line = ft_strjoin_gnl(line, *store);
		free(*store);
		*store = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static t_file node;
	char		*line;
	char		*buf;
	ssize_t		check;

	line = NULL;
	check = 0;
	if (fd < 0 || BUFFER_SIZE < 1 || BUFFER_SIZE > 2147483647)
		return (NULL);
    node = malloc(sizeof(t_file));
	node->fd = fd;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
	{
		ft_free_null(&line, &node->store, &buf);
		return (NULL);
	}
	buf[BUFFER_SIZE] = '\0';	
	check = append_buf(fd, &node->store, buf);
	if (check == -1)
	{
		ft_free_null(&line, &node->store, &buf);
		return (NULL);
	}
	line = find_line(&node->store);
	free(buf);
	return (line);
}

// int	main(void)
// {
// 	int	fd
// 	int	i;
// 	char *line;
	
// 	fd = open("file", O_RDONLY);
// 	i = 0;

// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	close(fd);
// 	printf("|||fd is: %d\n", fd);
// 	while (i++ < 2)
// 	{
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	}

// 	fd = open("file", O_RDONLY);
// 	i = 0;
// 	while (i++ < 4)
// 	{
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	}
// 	close(fd);
// }
