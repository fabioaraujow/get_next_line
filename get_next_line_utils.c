#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strchr(char *s, int c)
{
	char	to_find;
	char	*p;

	to_find = (char)c;
	if (to_find == '\0')
	{
		while (*s)
			s++;
		return (s);
	}
	while (*s)
	{
		if (*s == to_find)
			return (s);
		s++;
	}
	return (NULL);
}

static char	*ft_strjoin_ncase(char *s)
{
	size_t	i;
	char 	*buffer;

	i = 0;
	buffer = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (*s)
		buffer[i++] = *s++;
	buffer[i] = '\0';
	return (buffer);
}

char *ft_strjoin(char *s1, char *s2)
{
	char	*buffer;
	size_t	i;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1 || !s2)
	{
		if (!s1)
			return (ft_strjoin_ncase(s2));
		else
			return (ft_strjoin_ncase(s1));
	}
	buffer = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (*s1)
		buffer[i++] = *s1++;
	while(*s2)
		buffer[i++] = *s2++;
	buffer[i] = '\0';
	return (buffer);
}
