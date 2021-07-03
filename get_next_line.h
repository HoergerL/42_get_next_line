#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int	ft_strlcpy(char *dst, const char *src, int dstsize);
char	*ft_substr(char const *s, int start, int len);
int	ft_strlcat(char *dst, const char *src, int dstsize);
int get_next_line(int fd, char **line);

#endif
