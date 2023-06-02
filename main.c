// bgadzhil

# include "get_next_line.h"
# include <fcntl.h>		// ONLY FOR TESTING
# include <stdio.h>		// ONLY FOR TESTING

int		main(int ac, char **av)
{
	int		fd;
	char	*line;

	fd = open("./example.txt", O_RDONLY);
	line = av[ac - 1];
	while (line)
	{
		line = get_next_line(fd);
		printf("*** RESULT *** get_next_line():\t|%s|\n", line);
	}
	return (0);
}
