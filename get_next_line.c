/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhoerger <lhoerger@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 10:44:54 by lhoerger          #+#    #+#             */
/*   Updated: 2021/07/08 07:48:29 by lhoerger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char	*ft_strchr(const char *s, int c)
{
	int	cnt;
	int	len;

	len = ft_strlen(s);
	////printf("########len STRCHR: %i, %s\n", len, s);
	cnt = 0;
	while (cnt <= len)
	{
		////printf("if stört\n, s[cnt]: %i, c: %i\n", s[cnt], c);
		if ((int) s[cnt] == c)
		{
			//write(1, "return wird ausgeführt", 10);
			return ((char *) &s[cnt]);
		}
		cnt++;
	}
	return ((void *) 0);
}

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
	////printf("len: %i\n", len);
	s2 = calloc(len + 1, sizeof(char));
	if (!s2)
		return (0);
	
	ft_strlcpy((char *) s2, s1, len + 1);
	return (s2);
}

int ft_get_next_line(char *buffer, int *j, char **rest,char **line )
{
	char	*chr = NULL;
	int index_found;
	int status;
	char* s;
	char* new_line;

	index_found = BUFFER_SIZE;

	status = 2;
	// if (buffer[0] == '\0')
	// 	return (0); //überarbeitbar
			//EOF
	////printf("j: %i\n", *j);
	if (*j == -1)
		return (-1);
	if (*j == 0)
	{
		//printf("j=0");
		if(!line)
			return (-1);
		////printf("j = 0\n");
		return (0);

	}

	else if (*j > 0)
	{
		buffer[*j] = '\0';
		chr = ft_strchr(buffer, '\n');
		//write (1, "CHR funktioniert", 10);
		//////printf("Chr ist durchgelaufen: %p,  buffer:%p ", chr, buffer);
		////printf("chr: %s\n j: %i\n,buffer: %s\n len line: %i\n", chr, (int) *j, buffer, ft_strlen(*line));
		//write(1, "nach////printf", 10);
		if (chr != NULL)
		{
			status = 1;
			index_found = chr - buffer;
			////printf("buffer: %p, chr: %p\n", buffer, chr);
			*rest = ft_substr(buffer, index_found + 1, BUFFER_SIZE - index_found + 1);
			if(!(*rest))
				return (-1);
			//printf("buffer: %s, rest: %s, index_found: %i, BUFFER_SIZE - index_found + 1: %i \n", buffer, *rest, index_found, BUFFER_SIZE - index_found + 1);
		}
		else if (*j < BUFFER_SIZE)
			status = 0;
		else
			index_found = BUFFER_SIZE;			
		
		// test code
		s = ft_substr(buffer, 0, index_found);
		if(!(*buffer)) // ADDED
			return (-1); // ADDED
		// //printf("s: %p\n", s);
		//write(1, "nach s an\n", 10);
		//printf("s: %s\n", s);
		if((*line))
		
			new_line = ft_strjoin(*line, s);
		else 
		{
			//printf("else");
			new_line = ft_strdup(s);
			//printf("else, new_line: %s\n", new_line);
		}
		//printf("unter if, new_line: %s\n", new_line);
		free(s);
		s = NULL;
		//printf("unter erstem free\n");
		if (*line)   // WORKS
		 	free(*line); /// WORKS
		//printf("unter if \n");
		*line = ft_strdup(new_line);
		 //printf("line: %s\n", *line);
		//write(1, "unten\n", 7);
		free(new_line);
		new_line = NULL;
		
		
		//ft_strlcat(*line, buffer,  ft_strlen(*line) + index_found + 1);
		////printf("len line: %i, index_found: %i\n", ft_strlen(*line), index_found);
		//printf("len(line) + index+1: %i,line: %s, status: %i\n", ft_strlen(*line) + index_found + 1, *line, (int)status );
	}
	return (status);
}

char *get_next_line(int fd)
{
	char *buffer;
	static char	*rest = NULL;
	char *line;
	//static size_t i = 0;
	int status;
	int j;

	if(fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	j = BUFFER_SIZE;
	status = 2;	
	line = NULL;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	//write(1, "function begin", 10);
	if((!buffer))
		return (NULL);
	if(rest != NULL && rest[0] != 0)
	{
		 ft_strlcpy(buffer, rest, ft_strlen(rest) + 1);
		 free(rest);
		 rest = NULL;
		 status = ft_get_next_line(buffer, &j, &rest, &line);
	}
	while(status == 2 && j == BUFFER_SIZE)
	{
		//write(1, "while begin", 10);
		j = read(fd, buffer, BUFFER_SIZE);
		status = ft_get_next_line(buffer, &j, &rest, &line);
		//write(1, "nach func", 10);
		if(status != 2 && line == NULL)
			return (NULL);
		//printf("#########################line: %s\n", line);
		////printf("status in while: %i\n", (int) status);
	}
	free(buffer);
	buffer = NULL;
	//*line[i] = '\0';
	
	//////printf("i: %i\n", (int) i);
	
	//printf("#####################read: line:%s, rest: %s\n",line, rest);
	return line;
}

// int main(void) {
// 	int f = open("text.txt", O_RDONLY);
// 	// //printf("return: %i\n", get_next_line(f, &ptr));
// 	get_next_line(f);
// 	//printf("1. %s\n", ptr);
// 	get_next_line(f);
// 	//printf("2. %s\n", ptr);
// 	get_next_line(f);
// 	//printf("3. %s\n", ptr);
// 	////printf("EXTRA return: %i\n", get_next_line(f, &ptr));
// 	close(f);
// 	return 1;
// }
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	int		i;

	i = 0;
	fd = open("41_no_nl", O_RDONLY);
	//fd = open("test.txt", O_RDONLY);
	while (i < 3)
	{
		printf("line: %s", get_next_line(fd));
		i++;
	}
}

