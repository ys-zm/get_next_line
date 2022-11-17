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

size_t	check_pos_nl(char *buf)
{
	size_t	i;

	i = 0;
	while (buf[i] != '\n' && buf[i] != '\0')
		i++;
	return (i);
}

//check if null terminator is before buffer is full
//check if '\n' '\0' (last nl char)
//len of buf is smaller than buf_size
size_t	check_end(char *buf)
{
	if (check_pos_nl(buf) == ft_strlen(buf) && ft_strlen(buf) < BUFFER_SIZE )
		return (1);
	return (0);
}

void	move_chars(char *buf, size_t i)
{
	size_t	x;

	x = i;
	while (buf[i] != 0)
	{
		buf[i - x] = buf[i];
		i++;
	}
	buf[i - x] = '\0';
}

static ssize_t	extract_line(char **line, char *buf)
{
	size_t	new_line;

	new_line = check_pos_nl(buf);
	// printf("%zu", new_line);
	*line = ft_strjoin_gnl(*line, buf, new_line);
	if (!line)
		return (-1);
	if (new_line == BUFFER_SIZE && BUFFER_SIZE != 1)
		return (0);
	else
	{
		move_chars(buf, (new_line + 1));
		return (1);
	}
}


char	*get_next_line(int fd)
{
	char			*line;
	static char		buf[BUFFER_SIZE + 1];
	ssize_t			r;
	int				status;
	static ssize_t	sof;

	// if (! buf)
	// {
	// 	*(buf + BUFFER_SIZE) = '\0';
	// }
	//buf[0] = 0;
	buf[BUFFER_SIZE] = 0;
	line = NULL;
	sof = 1;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	while (1)
	{
		if (ft_strlen(buf) == 0 || sof == 1)
		{
			r = read(fd, buf, BUFFER_SIZE);
			buf[r] = '\0';
			sof = 0;
		}
		if (r < 0 || r == 0)
			return (NULL);
		status = extract_line(&line, buf);
		if (status == 1)
			return (line);
		// else if (status == -1)
		// {
		// 	if (line)
		// 		free(line);
		// 	return (NULL);
		// }
		
	}
}

void	ft_write_line(char *str)
{
	size_t	size;

	size = ft_strlen(str);
	write(1, str, size);
}

int	main(void)
{
	int	fd;
	int	i;
	char *line;
	
	fd = open("file2", O_RDONLY);
	i = 0;
	while (line)
	{
	line = get_next_line(fd);
	printf("%s", line);
	i++;
	}
	
	close(fd);
}

