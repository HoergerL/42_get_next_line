/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhoerger <lhoerger@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 07:57:56 by lhoerger          #+#    #+#             */
/*   Updated: 2021/07/15 14:15:09 by lhoerger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned int		c;
	unsigned char		*t;

	c = 0;
	t = (unsigned char *)s;
	while (n > c)
	{
		t[c] = '\0';
		c++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*point;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	point = malloc(size * count);
	if (!point)
		return ((void *) NULL);
	ft_bzero(point, size * count);
	return ((void *) point);
}


//#include <stddef.h>
//#include <stdlib.h>
//void * calloc (size_t nelem, size_t elsize)
//{
//  register void * ptr;  
//  if (nelem == 0 || elsize == 0)
//    nelem = elsize = 1;
  
//  ptr = malloc (nelem * elsize);
//  if (ptr) bzero (ptr, nelem * elsize);
  
//  return ptr;
//}
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*src2;
	unsigned char	*dest2;

	if (dst == 0 && src == 0)
		return (0);
	src2 = (unsigned char *) src;
	dest2 = (unsigned char *) dst;
	i = 0;
	while (i < n)
	{
		dest2[i] = src2[i];
		i++;
	}
	return (dst);
}

int	ft_strlen(const char *s)
{
	int	cnt;

	cnt = 0;
	if (!s)
		return (0);
	while (s[cnt] != '\0')
	{
		cnt++;
	}
	return (cnt);
}

char	*ft_substr(char const *s, int start, int len)
{
	char	*s2;
	int		len_substr;

	if (!s)
		return (0);
	if (len == 0)
	{
		s2 = calloc(1, 1);
		return (s2);
	}
	if (len == 0 || start >= ft_strlen(s))
	{
		s2 = calloc(1, 1);
		return (s2);
	}
	len_substr = strlen(&s[start]);
	if (len_substr > len)
		len_substr = len;
	s2 = calloc(len + 1, 1);
	if (!s2)
		return (0);
	ft_memcpy(s2, &s[start], len_substr);
	s2[len_substr] = '\0';
	return (s2);
}

char	*ft_strchr(const char *s, int c)
{
	int	cnt;
	int	len;

	len = ft_strlen(s);
	cnt = 0;
	while (cnt <= len)
	{
		if ((int) s[cnt] == c)
			return ((char *) &s[cnt]);
		cnt++;
	}
	return ((void *) 0);
}
