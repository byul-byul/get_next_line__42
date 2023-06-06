// bgadzhil

#include "get_next_line.h"

static void		show_buff_content(char buff[BUFFER_SIZE])
{
	int		i = -1;

	printf("[");
	while (++i < BUFFER_SIZE)
	{
		if (buff[i] == '\0')
			printf("_,");
		else if (buff[i] == '\n')
			printf("\\,");
		else
			printf("%c,", buff[i]);
	}
	printf("]\n");
}

static void	update_buff(char buff[BUFFER_SIZE], int s, int f)
{
	// int	i = -1;
	
	// printf("-- update_buff(): before:\t\tfirst_non_null_char_pos = |%d|, separator_pos = |%d|, buff = |", s, f);
	// while (++i < BUFFER_SIZE)
	// {
	// 	if (buff[i] == '\0')
	// 		printf("_,");
	// 	else
	// 		printf("%c,", buff[i]);
	// }
	// printf("|\n");
	while (s <= f)
	{
		buff[s] = '\0';
		s++;
	}
	// i = -1;
	// printf("-- update_buff():  after:\t\tfirst_non_null_char_pos = |%d|, separator_pos = |%d|, buff = |", s, f);
	// while (++i < BUFFER_SIZE)
	// {
	// 	if (buff[i] == '\0')
	// 		printf("_,");
	// 	else
	// 		printf("%c,", buff[i]);
	// }
	// printf("|\n");
}

static int	get_first_first_non_null_char_pos(char buff[BUFFER_SIZE])
{
	int	i;

	i = -1;
	while (++i < BUFFER_SIZE)
		if (buff[i] != '\0')
			return (i);
	return (-1);
}

static char	*safe_free(char *str)
{
	if (str)
		free(str);
	return (NULL);
}

static int	is_buff_empty(char buff[BUFFER_SIZE])
{
	int		i;

	i = 0;

	if (buff[0] != '\0' || buff[BUFFER_SIZE - 1] != '\0')
		return (0);
	while (++i < BUFFER_SIZE - 1)
		if (buff[i] != '\0')
			return (0);
	return (1);
}

static int	gnl_handler(char **line, char buff[BUFFER_SIZE])
{
	int		first_non_null_char_pos;
	int		separator_pos;
	char	*tmp_line;
	int		res;

	if ((*line)[0] == '\0' && is_buff_empty(buff))
		return (-1);
	if ((*line)[0] != '\0' && is_buff_empty(buff))
		return (1);
	tmp_line = *line;
	res = 1;
	separator_pos = ft_findcharl(buff, SEPARATOR, BUFFER_SIZE);
	first_non_null_char_pos = get_first_first_non_null_char_pos(buff);
	if (separator_pos == -1)
	{
		separator_pos = BUFFER_SIZE;
		res = 0;
	}
	printf("line before = |%s|\n", *line);
	// printf("-- gnl_handler(): before:\t\tline = |%s|, buff = |%s|, sep = |%d|, ff = |%d|\n", *line, &(buff[first_non_null_char_pos]), separator_pos, first_non_null_char_pos);
	*line = ft_strljoin(*line, &(buff[first_non_null_char_pos]), ft_strlen(*line), separator_pos - first_non_null_char_pos);
	safe_free(tmp_line);
	printf("buff_content(%d, %d)\tbefore update: ", first_non_null_char_pos, separator_pos);
	show_buff_content(buff);
	update_buff(buff, first_non_null_char_pos, separator_pos);
	printf("buff_content(%d, %d)\tafter  update: ", first_non_null_char_pos, separator_pos);
	show_buff_content(buff);
	// printf("-- gnl_handler():  after:\t\tline = |%s|, buff = |%s|, sep = |%d|, ff = |%d|\n", *line, &(buff[first_non_null_char_pos]), separator_pos, first_non_null_char_pos);
	if (!line)
		res = -1;
	printf("line after  = |%s|\n", *line);
	// printf("res = %d\n", res);
	// if (first_non_null_char_pos == -1)
	// 	exit(1);
	return (res);
}

char		*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE];
	int			gnl_handler_result;
	char		*line;
	int			i = 0; // TESTING

	line = malloc(1);
	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0 || !line)
		return (NULL);
	line[0] = '\0';
	while (1)
	{
		i++;
		// printf("\niter №_%d before reading:\t\tline = |%s|, buff = |%s|\n", i, line, buff);
		if (is_buff_empty(buff))
			if (read(fd, buff, BUFFER_SIZE) < 0)
			{
				// printf("iter №_%d READ FAILS!!!:\t\tline = |%s|, buff = |%s|\n", i, line, buff);
				return (safe_free(line));
			}
		// printf("iter №_%d before handling:\t\tline = |%s|, buff = |%s|\n", i, line, buff);
		gnl_handler_result = gnl_handler(&line, buff);
		// printf("iter №_%d after  handling:\t\tline = |%s|, buff = |%s|\n", i, line, buff);
		if (gnl_handler_result == -1)
			return (safe_free(line));
		if (gnl_handler_result == 1)
			return (line);
	}
}
