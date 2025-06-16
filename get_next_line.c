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
	char			*buffer;
	static char		*newline;
	static char		*stash;
	static size_t	byte_count;

	buffer = calloc(BUFFER_SIZE + 1, sizeof(char));

	if (newline != NULL)
		stash = newline + 1;
	else
		stash = ft_strdup("");

	/* printf("newline:%s\n", new_line); */
	newline = ft_strchr(buffer, '\n');

	byte_count = read(fd, buffer, BUFFER_SIZE);
	if (byte_count == 0)
	{
		free(buffer);
		free(stash);
		free(newline);
		stash = NULL;
		return (stash);
	}

	while (newline == NULL)
	{
		read(fd, buffer, BUFFER_SIZE);
		newline = ft_strchr(buffer, '\n');
		if (newline != NULL)
			stash = ft_strjoin(stash, buffer);
		else
		{
			// TODO: Add to stash only until the line break
			size_t chars_before_newline = &newline - &buffer;
			printf("pointer:%ld\n", chars_before_newline);
			/* stash = ft_strjoin(stash, buffer); */
		}
		printf("stash1:%s\n", stash);
	}
	printf("newline:%s\n", newline);
	printf("stash2:%s\n", stash);
	free (buffer);
	return (stash);
}
