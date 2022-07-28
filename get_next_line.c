/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chukim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 02:30:53 by chukim            #+#    #+#             */
/*   Updated: 2021/12/31 05:06:16 by chukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	read_file(int fd, char **buffer, char **current, char **line);
char	*output(char **current, char **line);

char	*get_next_line(int fd)
{
	static char	*current = NULL;
	char		*buffer;
	char		*line;
	ssize_t		n;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	if (read(fd, buffer, 0) < 0)
	{
		free(buffer);
		return (NULL);
	}
	if (current == NULL)
		current = ft_strdup("");
	n = read_file(fd, &buffer, &current, &line);
	if (n == 0 && line == NULL)
		return (NULL);
	return (line);
}

ssize_t	read_file(int fd, char **buffer, char **current, char **line)
{
	char	*temp;
	ssize_t	n;

	n = 1;
	while ((ft_strchr(*current, '\n') == NULL) && n)
	{
		n = read(fd, *buffer, BUFFER_SIZE);
		(*buffer)[n] = '\0';
		temp = *current;
		*current = ft_strjoin(temp, *buffer);
		free(temp);
	}
	free(*buffer);
	*buffer = NULL;
	*current = output(current, line);
	if (**line == '\0')
	{
		free(*line);
		*line = NULL;
	}
	return (n);
}

char	*output(char **current, char **line)
{
	size_t	i;
	char	*buffer;

	i = 0;
	buffer = NULL;
	while ((*(*current + i) != '\n') && (*(*current + i) != '\0'))
		i++;
	if (*(*current + i) == '\n')
	{
		i++;
		*line = ft_substr(*current, 0, i);
		buffer = ft_strdup(*current + i);
	}
	else
		*line = ft_strdup(*current);
	free(*current);
	*current = NULL;
	return (buffer);
}
