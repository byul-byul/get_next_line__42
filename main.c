// bgadzhil

# include <fcntl.h>		// ONLY FOR TESTING

# include "get_next_line.h"

int		main(int ac, char **av)
{
	int		fd;
	char	*line;

	(void)ac;
	(void)av;
	fd = open("./example.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("result of get_next_line():\n%s\n", line);
	return (0);
}