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

char	*cut_rem(char *rem, size_t pos, size_t rem_len)
{
	char *str;

	str = ft_strdup_gnl(rem, pos, rem_len);
	free(rem);
	return (str);
}

char	*read_error(char *line, char *rem, char *buf)
{
	free(line);
	free(rem);
	free(buf);
	line = NULL;
	rem = NULL;
	buf = NULL;
	return (line);
}

void	read_rem(size_t *pos, size_t *rem_len, char *rem)
{
	*pos = check_pos_nl(rem);
	*rem_len  = ft_strlen(rem);
}

char	*append_buf(int fd, char **line, char *rem, char *buf)
{
	size_t	pos;
	ssize_t	r;
	size_t	rem_len;
	
	r = -2;
	while ((rem && *rem) || r == -2)
	{
		r = read(fd, buf, BUFFER_SIZE); 
		if (r == -1)
			read_error(*line, rem, buf);
		buf[r] = '\0';
		if (r > 0)
			rem = ft_strjoin_gnl(rem, buf);
		if (rem && *rem)
		{
			read_rem(&pos, &rem_len, rem);
			if ((rem[pos - 1] == '\n') || r == 0)
			{
				*line = ft_strdup_gnl(rem, 0, pos);
				rem = cut_rem(rem, pos, rem_len);
				return (rem);
			}
		}
	}
	free(rem);
	return (NULL);	
}

char	*get_next_line(int fd)
{
	static char	*rem = NULL;
	char		*line;
	char		*buf;

	line = NULL;
	if (read(fd, NULL, 0) == -1 || BUFFER_SIZE < 1 || BUFFER_SIZE > 2147483647)
		return (NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	buf[BUFFER_SIZE] = '\0';		
	rem = append_buf(fd, &line, rem, buf);
	if (line && ! *line)
		read_error(line, rem, buf);
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
