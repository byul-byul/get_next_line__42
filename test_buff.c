
# include <stdio.h>
# include <fcntl.h>		// ONLY FOR TESTING
# include <unistd.h>

#define BUFFER_SIZE	10

static void		show_buff_content(char buff[BUFFER_SIZE])
{
	int		i = -1;

	printf("|");
	while (++i < BUFFER_SIZE)
	{
		if (buff[i] == '\0')
			printf("_,");
		else
			printf("%c,", buff[i]);
	}
	printf("|\n");
}

int				main(void)
{
	static char	buff[BUFFER_SIZE];
	int			i = -1;
	int			fd;

	fd = open("./example.txt", O_RDONLY);
	printf("buff_content at the beginning: ");
	show_buff_content(buff);
	read(fd, buff, BUFFER_SIZE);
	// while (++i < BUFFER_SIZE)
	// 	buff[i] = 'a' + i;
	printf("buff_content after filling   : ");
	show_buff_content(buff);
	i = -1;
	while (++i < 6)
		buff[i] = '\0';
	printf("buff_content at the end      : ");
	show_buff_content(buff);
}