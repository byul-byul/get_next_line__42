// bgadzhil

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	ft_putchar(char *str)
{
	while (*str)
		write(1, str++, 1);
}

int		ft_strcpy(char *str1, char *str2)
{
	int	i;

	i = -1;
	while (str2[++i])
		str1[i] = str2[i];
	return (i);
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	char	*res;
	int		i;
	int		len;

	i = -1;
	len = 0;
	if (size == 0)
		return ((char *)malloc(0));
	res = (char *)malloc(sizeof(strs) + sizeof(sep) * (size - 1) + 1);
	if (res)
	{
		while (++i < size)
		{
			len += ft_strcpy(res + len, strs[i]);
			if (i < size - 1)
				len += ft_strcpy(res + len, sep);
		}
		*(res + len) = '\0';
	}
	return (res);
}

char	*ft_strdup(const char *s)
{
	char	*result;
	size_t	size;

	size = ft_strlen(s) + 1;
	result = (char *)malloc(size);
	if (result)
		ft_memcpy(result, s, size);
	return (result);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const char	*src_ptr;
	char		*dest_ptr;

	if (dest == src)
		return (dest);
	src_ptr = src;
	dest_ptr = dest;
	while (n--)
		*dest_ptr++ = *src_ptr++;
	return (dest);
}

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*result;
	size_t	str_len;

	if (!str)
		return (NULL);
	str_len = ft_strlen(str);
	if (start > str_len)
		return (ft_strdup(""));
	str_len -= start;
	str += start;
	if (len >= str_len)
		return (ft_strdup(str));
	result = malloc(len + 1);
	if (result)
	{
		ft_memcpy(result, str, len);
		result[len] = '\0';
	}
	return (result);
}

int		ft_chrinstr(const char *str, int c)
{
	int	i;

	i = -1;
	// printf("ft_chrinstr() has as a parameter c = %d and c = %c\n ans str = %s\n", c, c, str);
	while (str[++i])
		if (str[i] == (char)c)
			return (i);
	return (-1);
}

void	ft_straddstr(char **line1, char **line2)
{
	char	*tmp;

	tmp = *line1;
	*line1 = ft_strjoin(*line1, *line2);
	free(*tmp);
}