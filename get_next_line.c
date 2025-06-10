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
	size_t		byte_count;
	char		*buffer;
	static char	*stash;

	stash = malloc(1000 * sizeof(char));
	buffer = calloc(BUFFER_SIZE, sizeof(char));
	byte_count = read(fd, buffer, BUFFER_SIZE - 1);
	if (byte_count == 0)
	{
		// TODO:
		free(buffer);
		free(stash);
		return (NULL);
	}
	printf("%ld\n", read(fd, buffer, BUFFER_SIZE - 1));
	ft_strlcpy(stash, buffer, 1000);
	printf("stash:%s\n", stash);
	//TODO
	free(buffer);
	return (stash);
}

