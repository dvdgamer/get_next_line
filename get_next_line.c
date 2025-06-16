/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   get_next_line.c                                   :+:    :+:             */
/*                                                    +:+                     */
/*   By: dponte <dponte@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/06/08 16:07:35 by dponte       #+#    #+#                  */
/*   Updated: 2025/06/10 18:37:37 by dponte       ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			*tmp;
	char			*buffer;
	char			*line_break;
	static char		*stash;
	static size_t	byte_count;

	buffer = calloc(BUFFER_SIZE + 1, sizeof(char));

	line_break = ft_strchr(buffer, '\n');
	printf("line_break:%s\n", line_break);

	stash = ft_strdup("");

	byte_count = read(fd, buffer, BUFFER_SIZE);
	/* printf("buffer:%s\n", buffer); */
	if (byte_count == 0)
	{
		free(buffer);
		free(stash);
		return (NULL);
	}

	while (line_break == NULL)
	{
		stash = ft_strjoin(stash, buffer);
		read(fd, buffer, BUFFER_SIZE);
		line_break = ft_strchr(buffer, '\n');
		printf("stash1:%s\n", stash);
	}
	ft_strplit()
	stash = line_break + 1;
	printf("line_break:%s\n", line_break);
	printf("\\n found!\n");
	printf("stash2:%s\n", stash);
	return (stash);
}
