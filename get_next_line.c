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
	char			*is_line_break;
	static size_t	byte_count;
	char			*buffer;
	char			*tmp;
	char			*stash;

	buffer = calloc(BUFFER_SIZE + 1, sizeof(char));
	tmp = calloc(BUFFER_SIZE + 1, sizeof(char));
	stash = ft_strdup("");
	byte_count = read(fd, buffer, BUFFER_SIZE);
	printf("buffer:%s\n", buffer);
	if (byte_count == 0)
	{
		free(buffer);
		free(stash);
		return (NULL);
	}

	//TODO:while no \n keep reading the file

	if (ft_strchr(buffer, '\n') == NULL)
	{
		// add the these lines to the stash
		get_next_line(fd);
		stash = ft_strjoin(stash, buffer);
		printf("stash:%s\n", stash);
	}
	else
	{
		printf("\\n found!\n");
		printf("stash:%s\n", stash);
		return (stash);
	}
	// finally returning the string
	/* tmp = ft_strjoin(stash, buffer); */
	return (stash);
}
