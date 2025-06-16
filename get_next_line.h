#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 42
# define MAX_FD 1024

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
char    *ft_strdup(const char *s);
char    *ft_strchr(const char *str, int c);
char    *ft_strjoin(char const *s1, char const *s2);

#endif
