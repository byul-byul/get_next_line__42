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

char	*ft_strljoin(char const *s1, char const *s2, size_t s1_len, size_t s2_len)
{
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	result = malloc(s1_len + s2_len + 1);
	if (result)
	{
		ft_memcpy(result, s1, s1_len);
		ft_memcpy(result + s1_len, s2, s2_len + 1);
	}
	return (result);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = ft_strljoin(s1, s2, s1_len, s2_len);
	return (result);
}

int		ft_chrinstr(const char *str, int c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == (char)c)
			return (i);
	return (-1);
}
