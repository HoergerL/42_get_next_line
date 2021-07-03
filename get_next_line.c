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

#include "get_next_line.h"


char	*ft_strchr(const char *s, int c)
{
	int	cnt;
	int	len;

	len = ft_strlen(s);
	printf("########len STRCHR: %i\n", len);
	cnt = 0;
	while (cnt <= len)
	{
		if (s[cnt] == c)
			return ((char *) &s[cnt]);
		cnt++;
	}
	return ((void *) 0);
}

int ft_get_next_line(char *buffer, int *j, char **rest,char **line )
{
	char	*chr = NULL;
	int index_found;
	int status;

	index_found = BUFFER_SIZE;

	status = 2;
	// if (buffer[0] == '\0')
	// 	return (0); //überarbeitbar
			//EOF
	if (*j == -1)
		return (-1);
	if (*j == 0)
	{
		printf("j = 0\n");
		return (0);

	}

	else if (*j > 0)
	{
		buffer[*j] = '\0';
		chr = ft_strchr(buffer, '\n');
		printf("chr: %s\n j: %i\n,buffer: %s\n, len line: %i\n", chr, (int) *j, buffer, ft_strlen(*line));

		if (chr != NULL)
		{
			status = 1;
			index_found = chr - buffer;
			printf("buffer: %p, chr: %p\n", buffer, chr);
			*rest = ft_substr(buffer, index_found + 1, BUFFER_SIZE - index_found + 1);
			printf("buffer: %s, rest: %s, index_found: %i, BUFFER_SIZE - index_found + 1: %i \n", buffer, *rest, index_found, BUFFER_SIZE - index_found + 1);
		}
		else if (*j < BUFFER_SIZE)
			status = 0;
		else
			index_found = BUFFER_SIZE;			
		

		ft_strlcat(*line, buffer,  ft_strlen(*line) + index_found + 1);
		printf("len line: %i, index_found: %i\n", ft_strlen(*line), index_found);
		printf("len(line) + index+1: %i,line: %s, status: %i\n", ft_strlen(*line) + index_found + 1, *line, (int)status );
	}
	return (status);
}

int get_next_line(int fd, char **line)
{
	char *buffer;
	static char	*rest = NULL;
	//static size_t i = 0;
	int status;
	int j;

	if(fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	j = BUFFER_SIZE;
	status = 2;	
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	//status = 2 -> repeat
	//status 1 = line has been read
	if((!buffer)|| (!line))
		return (-1);
	printf("\n\n\n\n\nFunktion wird ausgeführt\n");
	printf("rest: %s\n", rest);
	if(rest != NULL && rest[0] != 0)
	{
		 //ft_strlcat(*line, rest, strlen(rest) + strlen(*line) + 1);
		 ft_strlcpy(buffer, rest, ft_strlen(rest) + 1);
		 printf("Resteverwertung: len: %i, buffer: %s\n", ft_strlen(rest), buffer);
		 rest = NULL;
		//free(rest);
		 status = ft_get_next_line(buffer, &j, &rest, line);
		 printf("JA ES IST DAS\n");

		//i += strlen(rest);
		
		//nicht einfach hinzufuegen, da koennte auch ein \n drin sein
		printf("line: %s\n", *line);
	}
	
	//i = 0;
	while(status == 2 && j == BUFFER_SIZE)
	{
		j = read(fd, buffer, BUFFER_SIZE);
		status = ft_get_next_line(buffer, &j, &rest, line);
		printf("status in while: %i\n", (int) status);
	}
	
	//*line[i] = '\0';
	
	//printf("i: %i\n", (int) i);
	printf("read: line:%s, rest: %s\n",*line, rest);
	return status;
}

// int main(void) {
// 	char *puffer = malloc(100);
// 	char **ptr = &puffer;
// 	int f = open("text.txt", O_RDONLY);
// 	printf("return: %i\n", get_next_line(f, ptr));
// 	printf("return: %i\n", get_next_line(f, ptr));
// 	printf("return: %i\n", get_next_line(f, ptr));
// 	printf("EXTRA return: %i\n", get_next_line(f, ptr));
// 	printf("EXTRA return: %i\n", get_next_line(f, ptr));
// 	close(f);
// 	return 1;
// }

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


