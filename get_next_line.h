#ifndef GNL_H
# define GNL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>		// ONLY FOR TESTING

# define BUFFER_SIZE	42
# define SEPARATOR		'\n'

char	*get_next_line(int fd);
char	*ft_strljoin(char const *s1, char const *s2, size_t s1_len, size_t s2_len);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_chrinstr(const char *str, int c);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *str);
size_t	ft_strcpy(char *dst, const char *src);
size_t	ft_findcharl(const char *str, int c, size_t len);

#endif