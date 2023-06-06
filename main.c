// bgadzhil

# include "get_next_line.h"
# include <fcntl.h>		// ONLY FOR TESTING
# include <stdio.h>		// ONLY FOR TESTING

int		main(int ac, char **av)
{
	int		fd;
	char	*line;
	// int		i = 10;

	fd = open("./example.txt", O_RDONLY);
	line = av[ac - 1];
	while (line)
	{
		line = get_next_line(fd);
		// printf("\n\n*** ****** ***\n");
		printf("*** RESULT *** get_next_line():\t|%s|\n", line);
		// printf("*** ****** ***\n\n");
	}
	return (0);
}
