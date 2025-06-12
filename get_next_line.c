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

	//TODO: dynamic allocation to stash? Double it if no \n before filling stash?
	stash = calloc(100000, sizeof(char));
	buffer = calloc(BUFFER_SIZE, sizeof(char));
	byte_count = read(fd, buffer, BUFFER_SIZE - 1);
	if (byte_count == 0)
	{
		free(buffer);
		free(stash);
		return (NULL);
	}
	printf("stash:%s\n", stash);
	printf("buffer:%s\n", buffer);
	free(buffer);
	return (stash);
}

int	add_line_to_tmp(char *buffer, char *tmp ,size_t size)
{
	size_t	i;
	int		ready_to_print;

	ready_to_print = 0;
	i = 0;
	while (i < size && buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
		{
			//TODO: print this line including '\n'
			// print tmp;
			free (tmp);
			return 1;
		}
	}
	return 0;
}
