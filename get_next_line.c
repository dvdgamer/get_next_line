/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   get_next_line.c                                   :+:    :+:             */
/*                                                    +:+                     */
/*   By: dponte <dponte@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/07/01 14:31:50 by dponte       #+#    #+#                  */
/*   Updated: 2025/07/01 16:15:30 by dponte       ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "get_next_line.h"

char	*get_result(char **stash, char *line_break)
{
	size_t		len;
	char		*result;

	len = (line_break + 1) - *stash;
	result = ft_substr(*stash, 0, len);
	*stash = ft_strdup(line_break + 1);
	return (result);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*result;
	char		*line_break;
	static char	*stash = NULL;
	size_t		byte_count;

	buffer = calloc(BUFFER_SIZE, sizeof(char));
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
		byte_count = read(fd, buffer, BUFFER_SIZE);
		stash = ft_strjoin(stash, buffer);
		line_break = ft_strchr(stash, '\n');
	}
	return (get_result(&stash, line_break));
}
