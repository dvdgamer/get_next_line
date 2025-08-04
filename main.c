#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include "get_next_line.h"

void test_gnl(const char *file)
{
	int		count;
	int		fd;
	char	*next_line;

	count = 1;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: Could not open file '%s'\n", file);
		return;
	}
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
	close(fd);
}

void test_all_files(void)
{
	DIR *dir;
	struct dirent *entry;
	char filepath[512];

	dir = opendir("tests");
	if (dir == NULL)
	{
		printf("Error: Could not open 'tests' directory\n");
		return;
	}

	while ((entry = readdir(dir)) != NULL)
	{
		// Skip . and .. directories
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;

		// Only test .txt files
		int len = strlen(entry->d_name);
		if (len > 4 && strcmp(entry->d_name + len - 4, ".txt") == 0)
		{
			snprintf(filepath, sizeof(filepath), "tests/%s", entry->d_name);
			test_gnl(filepath);
		}
	}
	closedir(dir);
}


int main(void)
{
	test_all_files();
	return (0);
}
