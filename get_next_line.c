/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   get_next_line.c                                   :+:    :+:             */
/*                                                    +:+                     */
/*   By: dponte <dponte@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/07/01 14:31:50 by dponte       #+#    #+#                  */
/*   Updated: 2025/07/05 13:03:50 by dponte       ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

char	*ft_strchr(const char *str, int c)
{
	unsigned char	ch;

	ch = (unsigned char)c;
	while (*str != ch)
	{
		if (*str == '\0')
			return (NULL);
		str++;
	}
	return ((char *) str);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			total_size;
	size_t			i;

	if (size && count > SIZE_MAX / size)
		return (NULL);
	total_size = count * size;
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < total_size)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

char	*get_result(char **stash, char *line_break)
{
	size_t		len;
	char		*result;
	char		*new_stash;

	len = (line_break + 1) - *stash;
	result = ft_substr(*stash, 0, len);
	if (result == NULL)
		return (NULL);
	new_stash = ft_strdup(line_break + 1);
	if (new_stash == NULL)
	{
		free (result);
		return (NULL);
	}
	free (*stash);
	*stash = new_stash;
	return (result);
}

char	*get_next_line(int fd)
{
	char			*buffer;
	char			*line_break;
	char			*tmp;
	static char		*stash = NULL;
	ssize_t			byte_count;

	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0)
		return (free (stash), stash = NULL, NULL);
	line_break = NULL;
	if (stash == NULL)
		stash = ft_strdup("");
	else
	{
		if (ft_strchr(stash, '\n') != NULL)
		{
			line_break = ft_strchr(stash, '\n');
			return (get_result(&stash, line_break));
		}
	}
	while (line_break == NULL)
	{
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (buffer == NULL)
			return (NULL);
		byte_count = read(fd, buffer, BUFFER_SIZE);
		if (byte_count == 0)
		{
			free (buffer);
			if (stash && *stash)
			{
				tmp = ft_strdup(stash);
				free (stash);
				stash = NULL;
				return (tmp);
			}
			free (stash);
			stash = NULL;
			return (NULL);
		}
		if (byte_count == -1)
		{
			free (stash);
			stash = NULL;
			free (buffer);
			return (NULL);
		}
		tmp = stash;
		stash = ft_strjoin(tmp, buffer);
		free(tmp);
		free(buffer);
		if (stash == NULL)
			return (NULL);
		line_break = ft_strchr(stash, '\n');
	}
	return (get_result(&stash, line_break));
}
