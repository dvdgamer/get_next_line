#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main(void)
{
	int		fd;
	char	*next_line;
	int		count;

	count = 1;
	fd = open("test.txt", O_RDONLY);
	/* while (count < 10) */
	while (1)
	{
		next_line = get_next_line(fd);
		if (next_line == NULL)
			break ;
		printf("\n------------------------\n");
		printf("[%d]:%s\n", count, next_line);
		count++;
		free (next_line);
		next_line = NULL;
	}
	free (next_line);
	next_line = NULL;

	close(fd);

	count = 1;
	fd = open("multiple_line_no_nl.txt", O_RDONLY);
	/* while (count < 10) */
	while (1)
	{
		next_line = get_next_line(fd);
		if (next_line == NULL)
			break ;
		printf("\n------------------------\n");
		printf("[%d]:%s\n", count, next_line);
		count++;
		free (next_line);
		next_line = NULL;
	}
	free (next_line);
	next_line = NULL;

	close(fd);
	return (0);
}
