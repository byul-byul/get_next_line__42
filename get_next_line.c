// bgadzhil

#include "get_next_line.h"

static void	update_static_buff(char buff[BUFFER_SIZE + 1], int sep_i)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = &(buff[sep_i + 1]);
	while (i <= BUFFER_SIZE)
	{
		if (*tmp == '\0')
			buff[i] = '\0';
		else
			buff[i] = *tmp;
		i++;
		tmp++;
	}
}

static int	update_params(char **line, char buff[BUFFER_SIZE + 1], int sep_i)
{
	char	*tmp;
	int		res;

	tmp = *line;
	if (sep_i == -1)
	{
		*line = ft_strljoin(*line, buff, ft_strlen(*line), ft_strlen(buff));
		update_static_buff(buff, BUFFER_SIZE);
		res = 0;
	}
	else
	{
		if (sep_i == 0)
			*line = ft_strjoin(*line, "\n");
		else
			*line = ft_strljoin(*line, buff, ft_strlen(*line), sep_i);
		update_static_buff(buff, sep_i);
		res = 1;
	}
	free(tmp);
	if (!*line)
		res = -1;
	return (res);
}

static int	gnl_handler(char **line, char buff[BUFFER_SIZE + 1])
{
	int		separator_index;
	int		result;					//  0 - a line without separator at the end;
									//  1 - a line with separator at the end;
	if (!(*line))					// -1 - an error occured.
	{
		*line = malloc(1);
		if (*line)
			(*line)[0] = '\0';
		else
			return (-1);
	}
	separator_index = ft_chrinstr(buff, SEPARATOR);
	result = update_params(line, buff, separator_index);
	return (result);
}

static char	*free_and_exit(char *str)
{
	if (str)
		free(str);
	return (NULL);
}

char		*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	int			gnl_handler_result;
	int			readed_byte_count;
	char		*line;
	
	line = NULL;
	readed_byte_count = 0;
	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	while (1)
	{
		if (buff[0] == '\0')
		{
			readed_byte_count = read(fd, buff, BUFFER_SIZE);
			if (readed_byte_count < 0 || (readed_byte_count == 0 && !line))
				return (free_and_exit(line));
			if (readed_byte_count == 0 && line)
				return (line);
		}
		gnl_handler_result = gnl_handler(&line, buff);
		if (gnl_handler_result == -1)
			return (free_and_exit(line));
		if (gnl_handler_result == 1)
			return (line);
	}
}
