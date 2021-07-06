#include "get_next_line.h"


int	ft_strlen(const char *s)
{
	int	cnt;

	cnt = 0;
	while (s[cnt] != '\0')
	{
		cnt++;
	}
	return (cnt);
}

int	ft_strlcpy(char *dst, const char *src, int dstsize)
{
	int	len_src;
	int	i;

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

char	*ft_substr(char const *s, int start, int len)
{
	char	*s2;
	int	len_substr;

	if (!s)
		return (0);
    if (len == 0)
	{
        s2 = calloc(1, 1);
		s2[0] = '\0';
		return (s2);
	}
     //write(1,"vor if", 6);
     //printf("s: %s, start: %i", s, start);
	len_substr = strlen(&s[start]);
    //write(1,"nach if", 6);
	if (len_substr > len)
		len_substr = len;
	s2 = calloc(len + 1, 1);
   
	if (len == 0 || start >= ft_strlen(s))
	{
       
		s2[0] = '\0';
		return (s2);
	}
	if (!s2)
		return (0);
	if (start > ft_strlen(s))
		return (s2);
	memcpy(s2, &s[start], len_substr);
	s2[len_substr] = '\0';
	return (s2);
}

int	ft_strlcat(char *dst, const char *src, int dstsize)
{
	int	len_dst;
	int	len_src;
	int	i;
	

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
