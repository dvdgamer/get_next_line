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

char *get_result(char **stash, char *buffer, char *line_break)
{
	size_t		len;
	char		*result;
	char		*tmp;

	len = (line_break + 1) - buffer;
	tmp = ft_substr(buffer, 0, len);
	result = ft_strjoin(*stash, tmp);
	*stash = ft_strdup(line_break + 1);
	return (result);
}

char *get_next_line(int fd)
{
	char		*buffer;
	char		*result;
	char		*line_break;
	int			len;
	static char *stash = NULL;
	size_t		byte_count;
	
	buffer = calloc(BUFFER_SIZE, sizeof(char));
	line_break = NULL;

	if (stash == NULL)
		stash = ft_strdup("");
	else
	{
		if (ft_strchr(stash, '\n'))
		{
			line_break = ft_strchr(stash, '\n');
			len = (line_break + 1) - stash;
			result = ft_substr(stash, 0, len);
			stash = ft_strdup(line_break + 1);
			printf("stash:%s\n", stash);
			return (result);
		}
	}

	while (line_break == NULL)
	{ // ft_read_and_add_to_stash()
		byte_count = read(fd, buffer, BUFFER_SIZE);
		line_break = ft_strchr(buffer, '\n');
		stash = ft_strjoin(stash, buffer);
	}
	// Once it finds the \n
	return (get_result(&stash, buffer, line_break));
}

