/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/11 11:33:58 by yzaim         #+#    #+#                 */
/*   Updated: 2022/11/11 15:10:34 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h" 


size_t	ft_strlen(char *str)
{
	size_t	count;

	count = 0;
	while (str && *str++)
		count++;
	return (count);
}

static size_t	check_empty_file(char *line, char *buf)
{
	size_t	sum;

	sum = ft_strlen(line) + ft_strlen(buf);
	if (sum)
		return (1);
	return (0);
}

char	*ft_strjoin_gnl(char *line, char *buf, size_t end)
{
	char	*ext_line;
	size_t	i;
	size_t	start;

	start = 0;
	if (!check_empty_file(line, buf))
		return (NULL);
	i = 0;
	ext_line = malloc(sizeof(char) * (ft_strlen(line) + end + 1));
	if (!ext_line)
		return (NULL);
	while (line && line[i])
	{
		ext_line[i] = line[i];
		i++;
	}
	while (buf[start] && start < end)
		ext_line[i++] = buf[start++];
	ext_line[i] = '\0';
	if (line)
		free(line);
	return (ext_line);
}

char	*ft_strsplit_gnl(char *excess, char *buf, size_t start)
{
	char	*rem;
	size_t	i;

	i = 0;
	rem = malloc(sizeof(char) * (ft_strlen(buf) - start + 2));
	if (!rem)
		return (NULL);
	while (buf[start] != 0)
		rem[i++] = buf[start++];
	rem[i] = '\0';
	if (excess)
		free(excess);
	return (rem);
}