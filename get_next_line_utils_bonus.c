/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_njoined_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/11 11:33:58 by yzaim         #+#    #+#                 */
/*   Updated: 2022/11/11 15:10:34 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h" 

size_t	ft_strlen(char *str)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (str && str[i++])
		count++;
	return (count);
}

static size_t	check_empty_file(char *str, char *buf)
{
	size_t	sum;

	sum = ft_strlen(str) + ft_strlen(buf);
	if (sum)
		return (1);
	return (0);
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

char	*ft_strjoin_gnl(char *str, char *buf)
{
	char	*joined;
	size_t	i;
	size_t	start;

	start = 0;
	i = 0;
	if (!check_empty_file(str, buf))
		return (NULL);
	joined = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(buf) + 1));
	if (!joined)
		return (NULL);
	while (str && str[i])
	{
		joined[i] = str[i];
		i++;
	}
	while (buf && buf[start])
		joined[i++] = buf[start++];
	joined[i] = '\0';
	if (str)
		free(str);
	return (joined);
}

char	*ft_strdup_gnl(char *str, size_t start, size_t end)
{
	char	*dup;
	size_t	i;

	if (!str)
		return (NULL);
	i = 0;
	dup = malloc(sizeof(char) * (end - start + 1));
	if (!dup)
		return (NULL);
	while (str[start] && start < end)
	{
		dup[i] = str[start];
		i++;
		start++;
	}
	dup[i] = '\0';
	return (dup);
}