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
	//printf("########len STRCHR: %i, %s\n", len, s);
	cnt = 0;
	while (cnt <= len)
	{
		//printf("if stört\n, s[cnt]: %i, c: %i\n", s[cnt], c);
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
	//printf("len: %i\n", len);
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

	index_found = BUFFER_SIZE;

	status = 2;
	// if (buffer[0] == '\0')
	// 	return (0); //überarbeitbar
			//EOF
	//printf("j: %i\n", *j);
	if (*j == -1)
		return (-1);
	if (*j == 0)
	{
		*line = ft_substr(buffer, 0, 0);
		if(!line)
			return (-1);
		//printf("j = 0\n");
		return (0);

	}

	else if (*j > 0)
	{
		buffer[*j] = '\0';
		chr = ft_strchr(buffer, '\n');
		//write (1, "CHR funktioniert", 10);
		////printf("Chr ist durchgelaufen: %p,  buffer:%p ", chr, buffer);
		////printf("chr: %s\n j: %i\n,buffer: %s\n, len line: %i\n", chr, (int) *j, buffer, ft_strlen(*line));
		//write(1, "nach//printf", 10);
		if (chr != NULL)
		{
			status = 1;
			index_found = chr - buffer;
			//printf("buffer: %p, chr: %p\n", buffer, chr);
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
		char* s;
		char* new_line;
		s = ft_substr(buffer, 0, index_found);
		if(!(*buffer)) // ADDED
			return (-1); // ADDED
		// printf("s: %p\n", s);
		//write(1, "nach s an\n", 10);
		if((*line))
			new_line = ft_strjoin(*line, s);
		else 
			new_line = ft_strdup(s);
		// printf("new_line: %p\n", new_line);
		//free(*line);
		free(s);
		s = NULL;
		//free(*line); // because line gets overwritten with dynamic memory in the next line
		//*line = NULL; // But, because *line might be empty we first check its content
		if (*line)   // WORKS
		 	free(*line); /// WORKS
		*line = ft_strdup(new_line);
		// printf("line: %p\n", *line);
		//write(1, "unten\n", 7);
		free(new_line);
		new_line = NULL;
		
		
		//ft_strlcat(*line, buffer,  ft_strlen(*line) + index_found + 1);
		//printf("len line: %i, index_found: %i\n", ft_strlen(*line), index_found);
		//printf("len(line) + index+1: %i,line: %s, status: %i\n", ft_strlen(*line) + index_found + 1, *line, (int)status );
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
	//printf("\n\n\n\n\nFunktion wird ausgeführt\n");
	//printf("rest: %s\n", rest);
	if(rest != NULL && rest[0] != 0)
	{
		 //ft_strlcat(*line, rest, strlen(rest) + strlen(*line) + 1);
		 ft_strlcpy(buffer, rest, ft_strlen(rest) + 1);
		 //printf("Resteverwertung: len: %i, buffer: %s\n", ft_strlen(rest), buffer);
		 free(rest);
		 rest = NULL;
		 status = ft_get_next_line(buffer, &j, &rest, line);
		 //printf("JA ES IST DAS\n");

		//i += strlen(rest);
		
		//nicht einfach hinzufuegen, da koennte auch ein \n drin sein
		//printf("line: %s\n", *line);
	}
	
	//i = 0;
	while(status == 2 && j == BUFFER_SIZE)
	{
		j = read(fd, buffer, BUFFER_SIZE);
		status = ft_get_next_line(buffer, &j, &rest, line);
		//printf("status in while: %i\n", (int) status);
	}
	free(buffer);
	buffer = NULL;
	//*line[i] = '\0';
	
	////printf("i: %i\n", (int) i);
	
	//printf("#####################read: line:%s, rest: %s\n",*line, rest);
	return status;
}

// int main(void) {
// 	char *puffer = malloc(100);
// 	char *ptr = puffer;
// 	int f = open("text.txt", O_RDONLY);
// 	// printf("return: %i\n", get_next_line(f, &ptr));
// 	get_next_line(f, &ptr);
// 	printf("1. %s\n", ptr);
// 	get_next_line(f, &ptr);
// 	printf("2. %s\n", ptr);
// 	get_next_line(f, &ptr);
// 	printf("3. %s\n", ptr);
// 	//printf("EXTRA return: %i\n", get_next_line(f, &ptr));
// 	free(puffer);
// 	close(f);
// 	return 1;
// }

// #include <fcntl.h>
// int main()
// {
//    //int     fd;
//    char    *line;
//    //int d = BUFFER_SIZE;
//    int f = open("text.txt", O_RDONLY);
// //    if (argc == 1)
// //        fd = 0;
// //    else if (argc == 2)
// //        fd = open(argv[1], O_RDONLY);
// //    else
// //        return (2);
//    while (get_next_line(f, &line) == 1)
//    {
//        //printf("%s\n", line);
//        free(line);
//    }
//    close(f);
// //    if (argc == 2)
// //        close(fd);
// }

//int main2(void) {
//	char puffer[100];
//	int f = open("text.txt", O_RDONLY);
//	read(f, &puffer, sizeof(puffer));
//	//printf("%s",puffer);
//	return EXIT_SUCCESS;
//}


