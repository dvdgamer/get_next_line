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
#include <string.h>
#include <unistd.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line_break;
	char		*result;
	static char	*stash = NULL;
	size_t 		len;
	char		*tmp;
	size_t		byte_count;

	buffer = calloc(BUFFER_SIZE + 1, sizeof(char));

	if (stash == NULL)
		stash = ft_strdup("");

	line_break = ft_strchr(stash, '\n');
	if (line_break)
	{
		len = (line_break + 1) - stash;
		tmp = ft_substr(stash, 0, len);
		stash = ft_strdup(line_break + 1);
		return (tmp);
	}

	//TODO: Add null check

	/* printf("stash before buffer is read:%s\n",stash); */
	byte_count = read(fd, buffer, BUFFER_SIZE);
	/* printf("Original buffer:%s\n", buffer); */
	if (byte_count < BUFFER_SIZE)
	{
		stash = ft_strjoin(stash, buffer); // malloc needs to be protected
		return (stash);
	}

	line_break = ft_strchr(buffer, '\n');

	if (line_break)
	{
		len = (line_break + 1) - buffer;
		tmp = ft_substr(buffer, 0, len); // malloc needs to be protected 
		result = ft_strjoin(stash, tmp); // malloc needs to be protected
		free(tmp);
		//FIX: Can't do this if it's the last line
		//Error occurs here
		stash = ft_strdup(line_break + 1); // malloc needs to be protected
		return (result);
	}
	else
	{
		while (line_break == NULL && byte_count == BUFFER_SIZE)
		{	
			stash = ft_strjoin(stash, buffer);
			free(buffer);
			byte_count = read(fd, buffer, BUFFER_SIZE);
			if (byte_count <= 0)
			{
				stash = ft_strjoin(stash, buffer);
				return stash;
			};
			line_break = ft_strchr(buffer, '\n');
		}
		
		// If there's a line break
		len = (line_break + 1) - buffer;
		tmp = ft_substr(buffer, 0, len);
		result = ft_strjoin(stash, tmp);
		stash = ft_strdup(line_break + 1);
		return (result);
	}
	free (buffer);
	if (stash)
	{
		free(stash);
		stash = NULL;
	}
	return (stash);
}
