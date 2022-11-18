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
	while (buf[i] != '\n' && buf[i] != '\0')
		i++;
	if (buf[i] == '\n')
		i++;
	return (i);
}

char	*get_excess(char *excess, char *buf, size_t pos)
{
	char	*temp;
	temp = ft_strsplit_gnl(excess, buf, pos);
	if (!temp)
			return (NULL);
	return (temp);
}

char *get_line(char *line, char *excess, char *buf, size_t pos)
{
	if (excess)
	{	line = ft_strjoin_gnl(line, excess, ft_strlen(excess));
		free(excess);
		if (!line)
			return (NULL);
	}
	line = ft_strjoin_gnl(line, buf, pos);
	if (!line)
		return (NULL);
	return (line);
}

char	*extract_line(int fd, char *line, char **excess, char *buf)
{
	size_t	pos;
	ssize_t	r;
	
	r = 1;
	while (r)
	{
		r = read(fd, buf, BUFFER_SIZE);
		buf[r] = '\0';
		pos = check_pos_nl(buf);
		if (pos == BUFFER_SIZE)
			line = get_line(line, *excess, buf, pos);
		else
		{
			line = get_line(line, *excess, buf, pos);
			*excess = get_excess(*excess, buf, pos);
			//printf("%s\n", *excess);
			return (line);
		}
	}
	return (NULL);	
}

char	*get_next_line(int fd)
{
	static char	*excess = NULL;
	char		*line;
	char		*buf;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE < 1 || BUFFER_SIZE > 2147483647)
		return (NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	buf[BUFFER_SIZE] = '\0';		
	line = extract_line(fd, line, &excess, buf);
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
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	// while (line)
// 	// {
// 	// line = get_next_line(fd);
// 	// printf("%s", line);
// 	// }
	
// 	close(fd);
// }

