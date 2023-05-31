#ifndef GNL_H
# define GNL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>		// ONLY FOR TESTING

# define BUFFER_SIZE	8
# define SEPARATOR		'\n'

// typedef struct s_params
// {
// 	static char	buff[BUFFER_SIZE + 1];
// 	char		*line;
// }				t_params;

char	*get_next_line(int fd);
void	ft_putchar(char *str);
int		ft_strcpy(char *str1, char *str2);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *str, unsigned int start, size_t len);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_chrinstr(const char *str, int c);
void	ft_straddstr(char **line1, char **line2);

#endif