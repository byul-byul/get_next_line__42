// bgadzhil

#include "get_next_line.h"

// static int	handle_static_buffer(char **line, char buff[BUFFER_SIZE + 1])
// {
// 	int		separator_pos;
// 	char	*tail;

// 	separator_pos = ft_chrinstr(buff, SEPARATOR);
// 	if (separator_pos != -1)
// 	{
// 		if (!*line)
// 		{
// 			*line = ft_substr(buff, 0, separator_pos);
// 		}
// 		else
// 		{
// 			tail = ft_substr(buff, 0, separator_pos);
// 			ft_straddstr(line, &tail);
// 		}
// 		buff[separator_pos] = '\0';
// 		if (ft_strlen(buff + separator_pos + 1) > 0)
// 			ft_strcpy(buff, buff + separator_pos);
// 		else
// 			buff[0] = '\0';
// 	}
// 	else
// 	{
// 		if (!*line)
// 		{
// 			*line = ft_strdup(buff);
// 		}
// 		else
// 		{
// 			tail = ft_substr(buff, 0, separator_pos);
// 			ft_straddstr(line, &tail);
// 		}
// 		buff[0] = '\0';
// 	}
// 	return (separator_pos);
// }

// static int	gnl_handler(char **line, char buff[BUFFER_SIZE + 1])
// {
// 	char	*tmp;
// 	int		separator_pos;

// 	if (buff[0] == '\0')
// 		return (0);
// 	separator_pos = ft_chrinstr(buff, SEPARATOR);
// 	if (separator_pos != -1)
// 	{
// 		tmp = *line;
// 		*line = ft_strljoin(*line, buff, ft_strlen(*line), separator_pos);
// 		free(tmp);
// 		if (*line)
// 			return (1);
// 		else
// 			return (-1);
// 	}
// 	else
// 	{
// 		tmp = *line;
// 		*line = ft_strljoin(*line, buff, ft_strlen(*line), ft_strlen(buff));
// 		free(tmp);
// 		return (1);
// 	}
// 	if (separator_pos == -1)
// 	{
// 		tmp = ft_strjoin(*line, buff);
// 		free(*line);
// 		*line = tmp;
// 		return (0);
// 	}
// 	else
// 	{
// 		buff[separator_pos] = '\0';
// 		tmp = ft_strjoin(*line, buff);
// 		ft_strcpy(buff, buff + separator_pos);
// 		free(*line);
// 		*line = tmp;
// 		return (1);
// 	}
// }
static void	update_static_buff(char buff[BUFFER_SIZE + 1], int pos)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = &(buff[pos + 1]);
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

static int	update_params(char **line, char buff[BUFFER_SIZE + 1], int pos)
{
	char	*tmp;
	int		res;
	// int		len;

	tmp = *line;
	if (pos == -1)
	{
		// printf("-BEFORE operation:\t\t\tpos = %d, line = |%s|, buff = |%s|\n", pos, *line, buff);
		*line = ft_strljoin(*line, buff, ft_strlen(*line), ft_strlen(buff));
		// buff[0] = '\0';
		update_static_buff(buff, BUFFER_SIZE);
		// printf("-AFTER operation:\t\t\tpos = %d, line = |%s|, buff = |%s|\n", pos, *line, buff);
		res = 0;
	}
	else if (pos == 0)
	{
		// ft_strcpy(buff, buff + pos + 1);
		*line = ft_strjoin(*line, "\n");
		update_static_buff(buff, pos);
		res = 1;
	}
	else
	{
		// printf("-BEFORE operation:\t\t\tpos = %d, line = |%s|, buff = |%s|\n", pos, *line, buff);
		*line = ft_strljoin(*line, buff, ft_strlen(*line), pos);
		update_static_buff(buff, pos);
		// len = ft_strlen(buff) - pos - 1;
		// ft_strcpy(buff, buff + pos + 1);
		// buff[len] = '\0';
		// printf("-AFTER operation:\t\t\tpos = %d, line = |%s|, buff = |%s|\n", pos, *line, buff);
		res = 1;
	}
	free(tmp);
	if (!*line)
		res = -1;
	// printf("-RETURN:\t\t\t\tres = %d\n", res);
	return (res);
}

static int	gnl_handler(char **line, char buff[BUFFER_SIZE + 1])
{
	int		separator_pos;
	int		result;		// 0 - a line without separator at the end; 1 - a line with separator at the end; -1 - error;

	if (!(*line))
	{
		*line = malloc(1);
		if (*line)
			(*line)[0] = '\0';
		else
			return (-1);
	}
	if (buff[0] == '\0')
		return (0);
	separator_pos = ft_chrinstr(buff, SEPARATOR);
	result = update_params(line, buff, separator_pos);
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
	int			i = 0; // TESTING
	
	line = NULL;
	readed_byte_count = -1;
	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	while (1)
	{
		i++;
		printf("\niter №_%d before reading:\t\tline = |%s|, buff = |%s|\n", i, line, buff);
		if (buff[0] == '\0')
		{
			readed_byte_count = read(fd, buff, BUFFER_SIZE);
			printf("iter №_%d after  reading:\t\tline = |%s|, buff = |%s|\n", i, line, buff);
			if (readed_byte_count < 0 || (readed_byte_count == 0 && !line))
				return (free_and_exit(line));
			if (readed_byte_count == 0 && line)
				return (line);
		}
		printf("iter №_%d before handler:\t\tline = |%s|, buff = |%s|\n", i, line, buff);
		gnl_handler_result = gnl_handler(&line, buff);
		printf("iter №_%d after  handler:\t\tline = |%s|, buff = |%s|\n", i, line, buff);
		if (gnl_handler_result == -1)
			return (free_and_exit(line));
		if (gnl_handler_result == 1)
			return (line);
		// if (readed_byte_count < BUFFER_SIZE)
		// 	return (line);
		// if (readed_byte_count == -1)
		// 	return (NULL);
		// else if (readed_byte_count < BUFFER_SIZE)
		// 	return (line);
		// return (line);
		// readed_byte_count = read(fd, buff, BUFFER_SIZE);
		// printf("iter №_%d after  reading:\t\tline = |%s|, buff = |%s|\n", i, line, buff);
	}
}
