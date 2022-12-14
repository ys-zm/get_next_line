/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/30 12:58:45 by yzaim         #+#    #+#                 */
/*   Updated: 2022/11/30 13:02:08 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

ssize_t	append_buf(int fd, char **store, char *buf)
{
	ssize_t	read_ret;

	read_ret = 1;
	while (read_ret)
	{
		read_ret = read(fd, buf, BUFFER_SIZE);
		if (read_ret <= 0)
			return (read_ret);
		buf[read_ret] = '\0';
		if (read_ret > 0)
			*store = ft_strjoin_gnl(*store, buf);
		if (*store == NULL)
			return (-1);
		if (store && check_char('\n', *store))
			return (0);
	}
	return (0);
}

char	*find_line(char **store)
{
	size_t	pos;
	char	*line;
	char	*store_temp;

	line = NULL;
	store_temp = NULL;
	if (store && *store && check_char('\n', *store))
	{
		pos = check_pos_nl(*store);
		line = ft_strdup_gnl(*store, 0, pos);
		store_temp = ft_strdup_gnl(*store, pos, ft_strlen(*store));
		free(*store);
		*store = store_temp;
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
	static char	*store[OPEN_MAX];
	char		*line;
	char		*buf;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE < 1 || BUFFER_SIZE > 2147483647)
		return (NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	buf[BUFFER_SIZE] = '\0';
	if (append_buf(fd, &store[fd], buf) == -1)
	{
		ft_free_null(&line, &store[fd], &buf);
		return (NULL);
	}
	line = find_line(&store[fd]);
	if (line == NULL)
	{
		ft_free_null(&line, &store[fd], &buf);
		return (NULL);
	}
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
