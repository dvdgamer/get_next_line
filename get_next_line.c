/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   get_next_line.c                                   :+:    :+:             */
/*                                                    +:+                     */
/*   By: dponte <dponte@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/06/08 16:07:35 by dponte       #+#    #+#                  */
/*   Updated: 2025/06/10 16:30:45 by dponte       ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	size_t		byte_count;
	char		*buffer;
	static char	*stash;

	
	buffer = calloc(BUFFER_SIZE ,sizeof(char));
		// if things go bad free buffer
	byte_count = read(fd, buffer, BUFFER_SIZE - 1);
	if (byte_count == 0)
		return (NULL);
	printf("%ld", read(fd, buffer, BUFFER_SIZE - 1));
	return (buffer);
}

