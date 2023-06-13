// bgadzhil

#include "get_next_line.h"

static char	*safe_free(char *str)
{
	if (str)
		free(str);
	return (NULL);
}


static int	get_begining_i(char buff[BUFFER_SIZE])
{
	int	i;

	i = -1;
	while (++i < BUFFER_SIZE)
		if (buff[i] != '\0')
			return (i);
	return (-1);
}

// static int	is_buff_empty(char buff[BUFFER_SIZE])
// {
// 	if (buff[0] != '\0' || buff[BUFFER_SIZE - 1] != '\0')
// 		return (0);
// 	if (get_begining_i(buff) == -1)
// 		return (1);
// 	else
// 		return (0);
// }

static int	update_params(char **line, char buff[BUFFER_SIZE], int beg_i, int sep_i)
{
	int		i;
	char	*tmp_line;

	i = -1;
	tmp_line = *line;
	if (sep_i == -1)
	{
		*line = ft_strjoin(*line, buff);
		sep_i = BUFFER_SIZE;
	}
	else
		*line = ft_strljoin(*line, &(buff[beg_i]), ft_strlen(*line), sep_i - beg_i);
	safe_free(tmp_line);
	if (!(*line))
		return (0);
	while (++i <= sep_i)
		buff[i] = '\0';
	return (1);
}

static int	gnl_handler(char **line, char buff[BUFFER_SIZE])
{
	int		begining_i;						// -1 - buff is empty.
	int		separator_i;					// -1 - separator not found.
	int		gnl_handler_result;				// -1 - an error occured; 0 - should read() more; 1 - line is ready to be returned.

	gnl_handler_result = 1;
	begining_i = get_begining_i(buff);
	separator_i = ft_findcharl(buff, SEPARATOR, BUFFER_SIZE);
	if ((*line)[0] == '\0' && begining_i == -1)
		return (-1);
	if ((*line)[0] != '\0' && begining_i == -1)
		return (1);
	if (separator_i == -1)
	{
		separator_i = BUFFER_SIZE;
		gnl_handler_result = 0;
	}
	if(!update_params(line, buff, begining_i, separator_i))
		gnl_handler_result = -1;
	return (gnl_handler_result);
}

char		*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE];
	int			gnl_handler_result;
	char		*line;

	line = malloc(1);
	if (!line || BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (safe_free(line));
	line[0] = '\0';
	while (1)
	{
		if (get_begining_i(buff) == -1)
			if (read(fd, buff, BUFFER_SIZE) < 0)
				return (safe_free(line));
		gnl_handler_result = gnl_handler(&line, buff);
		if (gnl_handler_result == -1)
			return (safe_free(line));
		if (gnl_handler_result == 1)
			return (line);
	}
}
