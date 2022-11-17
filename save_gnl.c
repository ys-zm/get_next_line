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

size_t	check_pos_nl(char *buf, size_t i)
{
	while (buf[i] != '\n' && buf[i] != '\0')
		i++;
	if (buf[i] == '\0')
		return (BUFFER_SIZE);
	return (i);
}

static ssize_t	extract_line(char **line, char *buf, size_t *index)
{
	size_t	new_line;
	size_t	end;

	end = ft_strlen(&buf[*index]);
	new_line = check_pos_nl(buf, *index);
	// printf("new_line %zu\n", new_line);	
	*line = ft_strjoin_gnl(*line, buf, *index, new_line);
	if (!line)
		return (-1);
	if (new_line == BUFFER_SIZE)
	{
		*index = BUFFER_SIZE;
		return (0);
	}
	// else if (new_line == *index && (end + new_line) < BUFFER_SIZE)
	// {
	// 	*index = end + new_line;
	// 	return (1);
	// }
	else
	{
		*index = new_line + 1;
		// printf("new_line %zu\n", new_line);
		return (1);
	}	
}

char	*get_next_line(int fd)
{
	//static struct s_list array;
	char			*line;
	static char		buf[BUFFER_SIZE + 1];
	static size_t	index;
	ssize_t			r;
	int				status;
	static ssize_t eof;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	while (1)
	{
		if (index == BUFFER_SIZE || index == 0)
		{
			r = read(fd, buf, BUFFER_SIZE);
			buf[r] = '\0';
			index = 0;
		}
		// printf("r: %ld\n", r);
		// printf("index: %zu\n", index);
		// printf("buf len: %zu\n", ft_strlen(buf));
		// if (ft_strlen(buf) < BUFFER_SIZE)
		// 	eof = 1;
		if (r < 0 || eof == 1)
		{
			if (line)
				free(line);
			return (NULL);
		}	
		status = extract_line(&line, buf, &index);
		if (status == 1)
			return (line);
		else if (status == -1)
		{
			if (line)
				free(line);
			return (NULL);
		}
		if (r == 0 || ft_strlen(buf) < BUFFER_SIZE)
		 	eof = 1;
	}
}

void	ft_write_line(char *str)
{
	size_t	size;

	size = ft_strlen(str);
	write(1, str, size);
}

// int	main(void)
// {
// 	int	fd;
// 	int	i;
// 	char *line;
// 	// char *string;
// 	// char buf[6] = "hello";

// 	// string = malloc(sizeof(char) * 6);
// 	// string[0] = 'h';
// 	// string[1] = 'h';
// 	// string[2] = 'h';
// 	// string[3] = 'h';
// 	// string[4] = 'h';
// 	// string[5] = 'h';
// 	// string[6] = '\0';
// 	// ft_write_line(ft_strjoin_gnl(string, buf, 0, 3));

// 	fd = open("file2", O_RDONLY);
// 	i = 0;
// 	line = get_next_line(fd);
// 	printf("%s\n", line);
// 	line = get_next_line(fd);
// 	printf("%s\n", line);	
// 	line = get_next_line(fd);
// 	printf("%s\n", line);	// line = get_next_line(fd);
// 	// while (line)
// 	// {
// 	// 	ft_write_line(line);
// 	// 	line = get_next_line(fd);
// 	// }
// 	close(fd);
// }

/*t_list	*set_struct(int fd)
{
	t_list struct *node;

	node.buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	*(node).fd = fd;
	node->fd = fd;

	while (node->next != 0)
		if (node->fd == fd)
			return (node)
}*/

+++++++++++++++++++++++++BETTER+++VERSION+++++++++++++++++++++++++

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

size_t	check_pos_nl(char *buf, size_t i)
{
	while (buf[i] != '\n' && buf[i] != '\0')
		i++;
	return (i);
}

size_t	check_last_nl(char *buf, size_t i)
{
	if (buf[i] == '\n')
		i++;
	if (buf[i] == '\0')
		return (i);
	return (0);
}

//check if null terminator is before buffer is full
//check if '\n' '\0' (last nl char)
//len of buf is smaller than buf_size
size_t	check_end(char *buf, size_t index)
{
	if ((check_pos_nl(buf, index) == ft_strlen(buf) || check_last_nl(buf, index)) && ft_strlen(buf) < BUFFER_SIZE )
		return (1);
	if (check_last_nl(buf, index))
		return (1);
	return (0);
}

static ssize_t	extract_line(char **line, char *buf, size_t *index)
{
	size_t	new_line;


	new_line = check_pos_nl(buf, *index);
	*line = ft_strjoin_gnl(*line, buf, *index, new_line);
	if (!line)
		return (-1);
	if (new_line == BUFFER_SIZE)
	{
		*index = BUFFER_SIZE;
		return (0);
	}
	else if (check_end(buf, *index))
	 	*index = BUFFER_SIZE;
	else
		*index = new_line + 1;
	return (1);
}


char	*get_next_line(int fd)
{
	char			*line;
	static char		buf[BUFFER_SIZE + 1];
	static size_t	index;
	ssize_t			r;
	int				status;
	static ssize_t	eof;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	while (1)
	{
		if (index == BUFFER_SIZE || index == 0)
		{
			r = read(fd, buf, BUFFER_SIZE);
			buf[r] = '\0';
			index = 0;
		}
		status = extract_line(&line, buf, &index);
		if (status == 1)
			return (line);
		else if (status == -1 || r < 0 || eof == 1)
		{
			if (line)
				free(line);
			return (NULL);
		}
		if (r == 0)
		 	eof = 1;
	}
}

void	ft_write_line(char *str)
{
	size_t	size;

	size = ft_strlen(str);
	write(1, str, size);
}

// int	main(void)
// {
// 	int	fd;
// 	int	i;
// 	char *line;
	
// 	fd = open("file2", O_RDONLY);
// 	i = 0;
// 	while (i++ < 11)
// 	{
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	}
	
// 	close(fd);
// }

