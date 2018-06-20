#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char **argv)
{
	int fd;
	char *line;

	if (argc < 2)
	{
		puts("Expected two arguments for main");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	while(get_next_line(fd, &line))
	{
		puts("AFTER CALLING GNL:");
		printf("%s", line);
	}
	close(fd);
}
