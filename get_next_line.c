/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhoerger <lhoerger@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 10:44:54 by lhoerger          #+#    #+#             */
/*   Updated: 2021/07/01 17:39:26 by lhoerger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

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

int get_next_line(int fd, char **line)
{
	char buffer[BUFFER_SIZE + 1];
	static char	*chr = NULL;
	static size_t i = 0;
	size_t index_found;
	size_t repeat;
	size_t j;

	j = BUFFER_SIZE;
	repeat = 1;
	
	printf("\n\n\n\n\nFunktion wird ausgeführt\n");
	if(chr != NULL)
	{
		//printf("if, %s, len: %i \n", chr, strlen(chr) + strlen(*line) + 1);
		ft_strlcat(*line, chr, strlen(chr) + strlen(*line) + 1);
		//nicht einfach hinzufuegen, da koennte auch ein \n drin sein
		//printf("line: %s\n", *line);
	}
	
	//i = 0;
	while(repeat && j == BUFFER_SIZE)
	{
		j = read(fd, &buffer, BUFFER_SIZE);
		printf("%i, %i", BUFFER_SIZE, j);
		if (j > 0)
		{
			buffer[BUFFER_SIZE] = '\0';
			chr = strchr(buffer, '\n');
			printf("p: %s\n j: %i\n,buffer: %s\n, i: %i\n", chr, (int) j, buffer, (int) i);

			if (chr != NULL)
			{
				repeat = 0;
				index_found = chr - buffer;
				if(j < BUFFER_SIZE)
				{
					chr = ft_substr(buffer, index_found + 1, BUFFER_SIZE - index_found + 2);
					return 0;
				}
				else
					chr = ft_substr(buffer, index_found + 1, BUFFER_SIZE - index_found + 2);
				//printf("if erreicht\n");
			}
			else
				index_found = BUFFER_SIZE;
			ft_strlcat(*line, buffer,  i + index_found + 1);
			//printf("i: %i,line: %s\n", i + index_found, *line);
			i += j;
		}
		
	}
	
	//*line[i] = '\0';
	
	//printf("i: %i\n", (int) i);
	printf("read: %s\n",*line);
}

int main(void) {
	char *puffer = malloc(100);
	char **ptr = &puffer;
	int f = open("text.txt", O_RDONLY);
	get_next_line(f, ptr);
	get_next_line(f, ptr);
	get_next_line(f, ptr);
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
