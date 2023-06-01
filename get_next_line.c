// bgadzhil

#include "get_next_line.h"

static int	handle_params(char **line, char buff[BUFFER_SIZE + 1])
{
	int		separator_pos;
	char	*tail;

	// printf("\n- handle_params(): 1 - BEFORE getting separator_pos\n\tline = |%s|; buff = |%s|; separator_pos = %d\n", *line, buff, separator_pos);
	separator_pos = ft_chrinstr(buff, SEPARATOR);
	printf("\n- handle_params(): 2 - AFTER getting separator_pos\n\tline = |%s|; buff = |%s|; separator_pos = %d\n", *line, buff, separator_pos);
	if (separator_pos != -1)
	{
		printf("- handle_params(): 1-1 - inside if BEFORE\n\tline = |%s|; buff = |%s|; separator_pos = %d\n", *line, buff, separator_pos);
		if (!*line)
		{
			printf("- handle_params(): 1-2 - inside if-if BEFORE ft_substr()\n\tline = |%s|; buff = |%s|; separator_pos = %d\n", *line, buff, separator_pos);
			*line = ft_substr(buff, 0, separator_pos);
			printf("- handle_params(): 1-3 - inside if-if AFTER ft_substr()\n\tline = |%s|; buff = |%s|; separator_pos = %d\n", *line, buff, separator_pos);
		}
		else
		{
			printf("- handle_params(): 1-4 - inside if-else BEFORE ft_straddstr()\n\tline = |%s|; buff = |%s|; separator_pos = %d\n", *line, buff, separator_pos);
			tail = ft_substr(buff, 0, separator_pos);
			ft_straddstr(line, &tail);
			printf("- handle_params(): 1-5 - inside if-else AFTER ft_straddstr()\n\tline = |%s|; buff = |%s|; separator_pos = %d\n", *line, buff, separator_pos);
		}
		buff[separator_pos] = '\0';
		printf("- handle_params(): 1-6 - inside if AFTER\n\tline = |%s|; buff = |%s|; separator_pos = %d\n", *line, buff, separator_pos);
		// printf("handle_params(): 3--1\nline = %s; buff = %s; separator_pos = %d\n", *line, buff, separator_pos);
		// printf("handle_params(): 3--2\nline = %s; buff[%d] = %c; separator_pos = %d\n", *line, separator_pos - 1, buff[separator_pos - 1],separator_pos);
		// printf("handle_params(): 3--3\nline = %s; buff[%d] = %c; separator_pos = %d\n", *line, separator_pos, buff[separator_pos],separator_pos);
		// printf("handle_params(): 3--4\nline = %s; buff[%d] = %c; separator_pos = %d\n", *line, separator_pos + 1, buff[separator_pos + 1],separator_pos);

		if (ft_strlen(buff + separator_pos + 1) > 0)
			ft_strcpy(buff, buff + separator_pos);
		else
			buff[0] = '\0';
		printf("- handle_params(): 1-7 - inside if AFTER ft_strcpy()\n\tline = |%s|; buff = |%s|; separator_pos = %d\n", *line, buff, separator_pos);
	}
	else
	{
		if (!*line)
		{
			printf("- handle_params(): 2-1 - inside else-if BEFORE ft_strdup()\n\tline = |%s|; buff = |%s|; separator_pos = %d\n", *line, buff, separator_pos);
			*line = ft_strdup(buff);
			printf("- handle_params(): 2-2 - inside else-if AFTER ft_strdup()\n\tline = |%s|; buff = |%s|; separator_pos = %d\n", *line, buff, separator_pos);
		}
		else
		{
			printf("- handle_params(): 2-3 - inside else-else BEFORE ft_straddstr()\n\tline = |%s|; buff = |%s|; separator_pos = %d\n", *line, buff, separator_pos);
			tail = ft_substr(buff, 0, separator_pos);
			ft_straddstr(line, &tail);
			printf("- handle_params(): 2-4 - inside else-else AFTER ft_straddstr()\n\tline = |%s|; buff = |%s|; separator_pos = %d\n", *line, buff, separator_pos);
		}
		buff[0] = '\0';
		printf("- handle_params(): 2-4 - inside ELSE AFTER \n\tline = |%s|; buff = |%s|; separator_pos = %d\n", *line, buff, separator_pos);
	}
	printf("- handle_params(): 3 - END\n\tline = |%s|; buff = |%s|; separator_pos = %d\n", *line, buff, separator_pos);
	return (separator_pos);
}

char		*get_next_line(int fd)
{
	int			readed_bytes_count;
	static char	buff[BUFFER_SIZE + 1];
	char		*line;
	
	line = NULL;
	printf("- get_next_line(): 1 - START\n\tline = |%s|; buff = |%s|;\n", line, buff);
	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	printf("- get_next_line(): 2 - CHECK SUCCESS\n\tline = |%s|; buff = |%s|;\n", line, buff);
	if (buff[0] != '\0')
		if (handle_params(&line, buff) != -1)
			return (line);
	printf("- get_next_line(): 3 - BEFORE LOOP\n\tline = |%s|; buff = |%s|;\n", line, buff);
	while (1)
	{
		printf("- get_next_line(): 3-1 - INSIDE LOOP BEFORE READ %d BYTES\n\tline = |%s|; buff = |%s|;\n", BUFFER_SIZE, line, buff);
		readed_bytes_count = read(fd, buff, BUFFER_SIZE);
		printf("- get_next_line(): 3-2 - INSIDE LOOP AFTER READ %d BYTES\n\tline = |%s|; buff = |%s|;\n", BUFFER_SIZE, line, buff);
		if (readed_bytes_count != -1)
			if (handle_params(&line, buff) != -1)
				break ;
	}
	printf("- get_next_line(): 4 - FINISH\n\tline = |%s|; buff = |%s|;\n", line, buff);
	return (line);
}
