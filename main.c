#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include "get_next_line.h"
#include "get_next_line_bonus.h"

#define NUM_MULTI_FD 3
#define MULTI_FD_FILES {"tests/41_with_nl", "tests/42_with_nl", "tests/43_with_nl"}

void test_multi_fd_bonus(void)
{
	const char	*files[NUM_MULTI_FD] = MULTI_FD_FILES;
	int			fds[NUM_MULTI_FD];
	char		*lines[NUM_MULTI_FD] = {NULL};
	int			i, active = NUM_MULTI_FD;

	printf("\n=== Multi-FD Bonus Test ===\n");
	// Open all files
	for (i = 0; i < NUM_MULTI_FD; i++) {
		fds[i] = open(files[i], O_RDONLY);
		if (fds[i] == -1) {
			printf("Error: Could not open file '%s'\n", files[i]);
			active--;
		}
	}

	int round = 1;
	while (active > 0) {
		printf("\n--- Round %d ---\n", round++);
		for (i = 0; i < NUM_MULTI_FD; i++) {
			if (fds[i] != -1) {
				lines[i] = get_next_line_bonus(fds[i]);
				if (lines[i]) {
					printf("[fd %d | %s]: %s", fds[i], files[i], lines[i]);
					free(lines[i]);
				} else {
					close(fds[i]);
					fds[i] = -1;
					active--;
				}
			}
		}
	}
	printf("=== End Multi-FD Bonus Test ===\n");
}

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

void test_gnl_bonus(const char *file)
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
		next_line = get_next_line_bonus(fd);
		if (next_line == NULL)
			break ;
		printf("\n[BONUS]------------------\n");
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
		// Create full path
		snprintf(filepath, sizeof(filepath), "tests/%s", entry->d_name);
		printf("%s\n", filepath);
		test_gnl(filepath);
	}
	closedir(dir);
}

void test_all_files_bonus(void)
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
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;
		snprintf(filepath, sizeof(filepath), "tests/%s", entry->d_name);
		printf("%s\n", filepath);
		test_gnl_bonus(filepath);
	}
	closedir(dir);
}


int main(void)
{
	test_all_files();
	test_all_files_bonus();
	test_multi_fd_bonus();
	return (0);
}
