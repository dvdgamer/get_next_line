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
	char			*buffer;
	static char		*line_break;
	static char		*stash;
	size_t 			len;
	char		*tmp;
	size_t	byte_count;

	buffer = calloc(BUFFER_SIZE + 1, sizeof(char));
	tmp = calloc(BUFFER_SIZE + 1, sizeof(char));

	if (stash == NULL)
		stash = ft_strdup("");
	else
	{
		if (ft_strchr(stash, '\n'))
		{
			line_break = ft_strchr(stash, '\n');
			printf("line_break1:%s\n", line_break + 1);
			len = line_break - buffer;
			printf("len:%ld\n", len);
			tmp = ft_substr(buffer, 0, len);
			printf("tmp1:%s\n", tmp);
			stash = line_break + 1;
			return (tmp);
		}
	}

	byte_count = read(fd, buffer, BUFFER_SIZE);
	if (byte_count == 0)
	{
		stash = ft_strjoin(stash, buffer);
		free(buffer);
		free(tmp);
		return (stash);
	}

	line_break = ft_strchr(buffer, '\n');
	printf("\nbuffer:%s\n", buffer);

	if (line_break)
	{
		line_break++;
		/* printf("\nline_break: %s\n", newline); */
		tmp = ft_strjoin(tmp, buffer - *line_break);
		printf("buffer - *line_break:%s\n", line_break - *buffer);
		stash = line_break;
		printf("tmp2:%s\n", tmp);
		printf("stash:%s\n", stash);
		return (tmp);
	}
	else
	{
		while (line_break == NULL)
		{	
			if (byte_count == 0)
			{
				stash = ft_strjoin(stash, buffer);
				free(buffer);
				free(tmp);
				return (stash);
			}
			line_break = ft_strchr(buffer, '\n');
			if (line_break == NULL)
			{
				stash = ft_strjoin(stash, buffer);
			}
			else
			{
				// TODO: Add to stash only until the line break
				stash = ft_strjoin(stash, buffer - (*line_break + 1));
				if(ft_strchr(stash, '\n') == NULL)
					return (stash);
				else
				{
					tmp = ft_strjoin(tmp, line_break + 1); //save it to stash
					ft_strjoin(stash, tmp);
					return (tmp);
				}
				//TODO: need to check if there's any \n in stash already
				/* stash = ft_strjoin(stash, buffer); */
			}
			byte_count = read(fd, buffer, BUFFER_SIZE);
		}
	}
	printf("stash2:%s\n", stash);
	free (buffer);
	return (stash);
}
