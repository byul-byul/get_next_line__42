// bgadzhil

#include "get_next_line.h"

static int	handle_params(char **line, char buff[BUFFER_SIZE + 1])
{
	int		separator_pos;
	char	*tail;

	separator_pos = ft_chrinstr(buff, SEPARATOR);
	printf("handle_params(): 1\nline = %s; buff = %s; separator_pos = %d\n", *line, buff, separator_pos);
	if (separator_pos != -1)
	{
		if (!*line)
		{
			*line = ft_substr(buff, 0, separator_pos);
			printf("handle_params(): 2\nline = %s; buff = %s; separator_pos = %d\n", *line, buff, separator_pos);
		}
		else
		{
			tail = ft_substr(buff, 0, separator_pos);
			ft_straddstr(line, &tail);
			printf("handle_params(): 3\nline = %s; buff = %s; separator_pos = %d\n", *line, buff, separator_pos);
		}
		buff[separator_pos] = '\0';
		ft_strcpy(buff, buff + separator_pos + 1);
		printf("handle_params(): 4\nline = %s; buff = %s; separator_pos = %d\n", *line, buff, separator_pos);
	}
	else
	{
		if (!*line)
		{
			*line = ft_strdup(buff);
			printf("handle_params(): 5\nline = %s; buff = %s; separator_pos = %d\n", *line, buff, separator_pos);
		}
		else
		{
			tail = ft_substr(buff, 0, separator_pos);
			ft_straddstr(line, &tail);
			printf("handle_params(): 6\nline = %s; buff = %s; separator_pos = %d\n", *line, buff, separator_pos);
		}
		buff[0] = '\0';
		printf("handle_params(): 7\nline = %s; buff = %s; separator_pos = %d\n", *line, buff, separator_pos);
	}
	printf("handle_params(): 8\nline = %s; buff = %s; separator_pos = %d\n", *line, buff, separator_pos);
	return (separator_pos);
}

char		*get_next_line(int fd)
{
	int			readed_bytes;
	static char	buff[BUFFER_SIZE + 1];
	char		*line;
	
	line = NULL;
	printf("---get_next_line(): 1\nline = %s; buff = %s\n", line, buff);
	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	printf("---get_next_line(): 2\nline = %s; buff = %s\n", line, buff);
	if (buff[0] != '\0')
		if (handle_params(&line, buff) != -1)
			return (line);
	printf("---get_next_line(): 3\nline = %s; buff = %s\n", line, buff);
	while (1)
	{
		readed_bytes = read(fd, buff, BUFFER_SIZE);
		printf("---get_next_line(): 4\nline = %s; buff = %s\n", line, buff);
		if (readed_bytes != -1)
			if (handle_params(&line, buff) != -1)
				break ;
	}
	printf("---get_next_line(): 5\nline = %s; buff = %s\n", line, buff);
	return (line);
}
