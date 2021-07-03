/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhoerger <lhoerger@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 10:44:54 by lhoerger          #+#    #+#             */
/*   Updated: 2021/07/02 11:01:31 by lhoerger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	len_src;
	unsigned int	i;

	len_src = 0;
	i = 0;
	if (dst == 0 && src == 0)
		return (0);
	while (src[len_src])
		len_src++;
	if (dstsize > 0)
	{
		while (src[i] && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len_src);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s2;
	size_t	len_substr;

	if (!s)
		return (0);
	len_substr = strlen(&s[start]);
	if (len_substr > len)
		len_substr = len;
	s2 = malloc(sizeof(char) * len + 1);
	if (len == 0 || start >= strlen(s))
	{
		s2[0] = '\0';
		return (s2);
	}
	if (!s2)
		return (0);
	if (start > strlen(s))
		return (s2);
	memcpy(s2, &s[start], len_substr);
	s2[len_substr] = '\0';
	return (s2);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	i;
	

	len_dst = 0;
	len_src = 0;
	if(!src)
		return 0;
	while (dst[len_dst] && len_dst < dstsize)
		len_dst++;
	while (src[len_src])
		len_src++;
	if (dstsize == 0)
		return (len_src);
	if (dstsize <= len_dst)
		return (dstsize + len_src);
	i = 0;
	while (--dstsize - len_dst && src[i])
	{
	//printf("strlcat: %c\n", src[i]);
		dst[len_dst + i] = src[i];
		i++;
	}
	dst[i + len_dst] = '\0';
	return (len_src + len_dst);
}

int ft_get_next_line(char *buffer, size_t *j, char **rest,char **line )
{
	char	*chr = NULL;
	size_t index_found;
	size_t status;

	status = 2;
	if (buffer[0] == '\0')
		return (0); //überarbeitbar
			//EOF
	if (*j == -1)
		return (-1);
	if (*j == 0)
		return (0);
	else if (*j > 0)
	{
		buffer[*j] = '\0';
		chr = strchr(buffer, '\n');
		printf("chr: %s\n j: %i\n,buffer: %s\n, len line: %i\n", chr, (int) *j, buffer, strlen(*line));

		if (chr != NULL)
		{
			status = 1;
			index_found = chr - buffer;
			*rest = ft_substr(buffer, index_found + 1, BUFFER_SIZE - index_found + 1);
			//printf("buffer: %s, rest: %s, index_found: %i, BUFFER_SIZE - index_found + 1: %i \n", buffer, *rest, index_found, BUFFER_SIZE - index_found + 1);
		}
		else if (*j < BUFFER_SIZE)
			return (0);
		else
			index_found = BUFFER_SIZE;			
		

		ft_strlcat(*line, buffer,  strlen(*line) + index_found + 1);
		//printf("i+index+1: %i,line: %s\n", strlen(*line) + index_found + 1, *line);
		//*i += *index_found;
	}
	return (status);
}

int get_next_line(int fd, char **line)
{
	char buffer[BUFFER_SIZE + 1];
	static char	*rest = NULL;
	//static size_t i = 0;
	size_t status;
	size_t j;

	j = BUFFER_SIZE;
	status = 2;	
	//status = 2 -> repeat
	//status 1 = line has been read
	if(fd < 0 || BUFFER_SIZE <= 0 || (!line))
		return (-1);
	//printf("\n\n\n\n\nFunktion wird ausgeführt\n");
	//printf("rest: %s\n", rest);
	if(rest != NULL && rest[0] != 0)
	{
		//printf("if, %s, len: %i \n", chr, strlen(chr) + strlen(*line) + 1);
		 //ft_strlcat(*line, rest, strlen(rest) + strlen(*line) + 1);
		 ft_strlcpy(buffer, rest, strlen(rest) + 1);
		 //printf("Resteverwertung: len: %i, buffer: %s\n", strlen(rest), buffer);
		// rest = NULL;
		 ft_get_next_line(buffer, &j, &rest, line);

		//i += strlen(rest);
		
		//nicht einfach hinzufuegen, da koennte auch ein \n drin sein
		//printf("line: %s\n", *line);
	}
	
	//i = 0;
	while(status == 2 && j == BUFFER_SIZE)
	{
		j = read(fd, &buffer, BUFFER_SIZE);
		status = ft_get_next_line(buffer, &j, &rest, line);
	}
	
	//*line[i] = '\0';
	
	//printf("i: %i\n", (int) i);
	printf("read: %s, rest: %s\n",*line, rest);
	return status;
}

int main(void) {
	char *puffer = malloc(100);
	char **ptr = &puffer;
	int f = open("text.txt", O_RDONLY);
	printf("return: %i\n", get_next_line(f, ptr));
printf("return: %i\n", get_next_line(f, ptr));
printf("return: %i\n", get_next_line(f, ptr));
	//get_next_line(f, ptr);
	close(f);
	return 1;
}

//#include <fcntl.h>
//int main(int argc, char **argv)
//{
//    int     fd;
//    char    *line;
//    int d = BUFFER_SIZE;
//    if (argc == 1)
//        fd = 0;
//    else if (argc == 2)
//        fd = open(argv[1], O_RDONLY);
//    else
//        return (2);
//    while (get_next_line(fd, &line) == 1)
//    {
//        printf("%s\n", line);
//        free(line);
//    }
//    if (argc == 2)
//        close(fd);
//}

//int main2(void) {
//	char puffer[100];
//	int f = open("text.txt", O_RDONLY);
//	read(f, &puffer, sizeof(puffer));
//	printf("%s",puffer);
//	return EXIT_SUCCESS;
//}

//char	*ft_strchr(const char *s, int c)
//{
//	int	cnt;
//	int	len;

//	len = ft_strlen(s);
//	cnt = 0;
//	while (cnt <= len)
//	{
//		if (s[cnt] == c)
//			return ((char *) &s[cnt]);
//		cnt++;
//	}
//	return ((void *) 0);
//}
