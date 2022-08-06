/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chukim <chukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 02:30:53 by chukim            #+#    #+#             */
/*   Updated: 2022/08/07 01:29:05 by chukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*output(t_arg *arg, char **current)
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
		arg->line = ft_substr(*current, 0, i);
		buffer = ft_strdup(*current + i);
	}
	else
		arg->line = ft_strdup(*current);
	free(*current);
	*current = NULL;
	return (buffer);
}

ssize_t	read_file(int fd, t_arg *arg, char **current)
{
	char	*temp;
	ssize_t	n;

	n = 1;
	while ((ft_strchr(*current, '\n') == NULL) && n) // current 안에 개행이 있거나, 0을 read하면 반복 종료
	{
		n = read(fd, arg->buffer, BUFFER_SIZE);
		(arg->buffer)[n] = '\0';
		temp = *current;
		*current = ft_strjoin(temp, arg->buffer); // current에 반환할 문자열만큼 저장
		free(temp);
	}
	free(arg->buffer);
	arg->buffer = NULL;
	*current = output(arg, current);
	if (*arg->line == '\0')
	{
		free(arg->line);
		arg->line = NULL;
	}
	return (n);
}

char	*get_next_line(int fd) // 정상일 때, 파일 1줄을 반환, 오류일 때, NULL을 반환
{
	static char	*current = NULL;
	t_arg		*arg;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	arg = (t_arg *)malloc(1 * sizeof(t_arg));
	arg->buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (arg->buffer == NULL)
	{
		free(arg);
		return (NULL);
	}
	if (read(fd, arg->buffer, 0) < 0) // 유효한 fd인지 확인 read(fd, buffer, 0)은 파일스트림을 움직이지 않음.
	{
		free(arg->buffer);
		free(arg);
		return (NULL);
	}
	if (current == NULL)
		current = ft_strdup("");
	arg->n = read_file(fd, arg, &current);
	if (arg->n == 0 && arg->line == NULL)
	{
		free(arg);
		return (NULL);
	}
	result = arg->line;
	free(arg);
	return (result);
}
