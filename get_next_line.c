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

char	*cut_excess(char *excess, size_t pos, size_t ex_size)
{
	char *temp;

	temp = ft_strsplit_gnl(excess, pos, ex_size);
	free(excess);
	return (temp);
}

void	gnl_free(char *str)
{
	free(str);
	str = NULL;
}

char	*extract_line(int fd, char **line, char *excess, char *buf)
{
	size_t	pos;
	ssize_t	r;
	size_t	ex_size;
	
	r = -2;
	while ((excess && *excess) || r == -2)
	{
		r = read(fd, buf, BUFFER_SIZE); //read protection
		buf[r] = '\0';
		if (r == -1)
		{
			gnl_free(excess);
			gnl_free(excess);
			return (NULL);
		}
		if (r > 0)
			excess = ft_strjoin_gnl(excess, buf);
		if (excess && *excess)
		{
			pos = check_pos_nl(excess);
			ex_size = ft_strlen(excess);
			if ((excess && excess[pos - 1] == '\n') || r == 0)
			{
				*line = ft_strsplit_gnl(excess, 0, pos);
				excess = cut_excess(excess, pos, ex_size);
				return (excess);
			}
		}
	}
	free(excess);
	return (NULL);	
}

char	*get_next_line(int fd)
{
	static char	*excess = NULL;
	char		*line;
	char		*buf;

	line = NULL;
	if (read(fd, NULL, 0) == -1 || BUFFER_SIZE < 1 || BUFFER_SIZE > 2147483647)
		return (NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	buf[BUFFER_SIZE] = '\0';		
	excess = extract_line(fd, &line, excess, buf);
	if (line && !*line)
		gnl_free(line);
	// if (excess && !*excess)
	// {
	// 	free(excess);
	// 	excess = NULL;
	// }
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


// 	// line = get_next_line(fd);
// 	// printf("%s", line);
// 	// line = get_next_line(fd);
// 	// printf("%s", line);
// 	// line = get_next_line(fd);
// 	// printf("%s", line);
// 	// line = get_next_line(fd);
// 	// printf("%s", line);
// 	while (i++ < 4)
// 	{
// 	printf("%s", line);
// 	line = get_next_line(fd);
// 	}
	
// 	close(fd);
// }

// int	main(void)
// {
// 	int	fd;
// 	int	i;
// 	char *line;
	
// 	fd = open("file", O_RDONLY);
// 	i = 0;

// 	while (i++ < 4)
// 	{
// 	line = get_next_line(fd);
// 	printf("%s\n", line);
// 	}
	
// 	close(fd);
// }
