/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhoerger <lhoerger@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 10:44:54 by lhoerger          #+#    #+#             */
/*   Updated: 2021/07/08 13:45:56 by lhoerger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	len;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	s3 = malloc(sizeof(char) * len);
	if (!s3)
		return (0);
	ft_strlcpy(s3, s1, ft_strlen(s1) + 1);
	ft_strlcat(s3, s2, len);
	return (s3);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		len;

	len = ft_strlen(s1);
	s2 = calloc(len + 1, sizeof(char));
	if (!s2)
		return (0);
	ft_strlcpy((char *) s2, s1, len + 1);
	return (s2);
}

int	ft_get_next_line(char *buffer, int *j, char **rest, char **line)
{
	char	*chr;
	int		found;
	int		status;
	char	*s;
	char	*new_line;

	chr = NULL;
	found = BUFFER_SIZE;
	status = 2;
	if (*j == -1)
		return (-1);
	if (*j == 0)
	{
		if (!line)
			return (-1);
		return (0);
	}
	else if (*j > 0)
	{
		buffer[*j] = '\0';
		chr = ft_strchr(buffer, '\n');
		if (chr != NULL)
		{
			status = 1;
			found = chr - buffer + 1;
			*rest = ft_substr(buffer, found + 1, BUFFER_SIZE - found + 1);
			if (!(*rest))
				return (-1);
		}
		else if (*j < BUFFER_SIZE)
			status = 0;
		else
			found = BUFFER_SIZE;
		s = ft_substr(buffer, 0, found);
		if (!(*buffer))
			return (-1);
		if ((*line))
			new_line = ft_strjoin(*line, s);
		else
			new_line = ft_strdup(s);
		free(s);
		s = NULL;
		if (*line)
			free(*line);
		*line = ft_strdup(new_line);
		free(new_line);
		new_line = NULL;
	}
	return (status);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*rest = NULL;
	char		*line;
	int			status;
	int			j;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	j = BUFFER_SIZE;
	status = 2;
	line = NULL;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if ((!buffer))
		return (NULL);
	if (rest != NULL && rest[0] != 0)
	{
		 ft_strlcpy(buffer, rest, ft_strlen(rest) + 1);
		 free(rest);
		 rest = NULL;
		 status = ft_get_next_line(buffer, &j, &rest, &line);
	}
	while (status == 2 && j == BUFFER_SIZE)
	{
		j = read(fd, buffer, BUFFER_SIZE);
		status = ft_get_next_line(buffer, &j, &rest, &line);
		if (status != 2 && line == NULL)
			return (NULL);
	}
	free(buffer);
	//buffer = NULL;
	return (line);
}

int	main(void)
{
	int		fd;
	int		i;

	i = 0;
	fd = open("41_with_nl", O_RDONLY);
	while (i < 3)
	{
		printf("line: %s", get_next_line(fd));
		i++;
	}
}
