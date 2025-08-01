/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   get_next_line.c                                   :+:    :+:             */
/*                                                    +:+                     */
/*   By: dponte <dponte@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/07/01 14:31:50 by dponte       #+#    #+#                  */
/*   Updated: 2025/07/05 13:03:50 by dponte       ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *str, int c)
{
	unsigned char	ch;

	ch = (unsigned char)c;
	while (*str != ch)
	{
		if (*str == '\0')
			return (NULL);
		str++;
	}
	return ((char *) str);
}

char	*get_result(char **stash, char *line_break)
{
	size_t		len;
	char		*result;
	char		*new_stash;

	len = (line_break + 1) - *stash;
	result = ft_substr(*stash, 0, len);
	if (result == NULL)
		return (NULL);
	new_stash = ft_strdup(line_break + 1);
	if (new_stash == NULL)
	{
		free (result);
		return (NULL);
	}
	free (*stash);
	*stash = new_stash;
	return (result);
}

char	*handle_eof(char **stash, char *tmp, char *buffer)
{
	free (buffer);
	if (*stash && **stash)
	{
		tmp = ft_strdup(*stash);
		free (*stash);
		*stash = NULL;
		return (tmp);
	}
	free (*stash);
	*stash = NULL;
	return (NULL);
}

//TODO: Make buffer double size to minimize malloc calls

char	*read_and_add_line_to_stash(char **stash, int fd)
{
	char		*tmp;
	char		*buffer;
	ssize_t		byte_count;

	while (ft_strchr(*stash, '\n') == NULL)
	{
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (buffer == NULL)
			return (NULL);
		byte_count = read(fd, buffer, BUFFER_SIZE);
		if (byte_count == 0)
			handle_eof(*&stash, tmp, buffer);
		if (byte_count == -1)
			return (free (*stash), free (buffer), *stash = NULL, NULL);
		if (*stash == NULL)
			return (NULL);
		tmp = *stash;
		*stash = ft_strjoin(tmp, buffer);
		free(tmp);
		free(buffer);
	}
	return (get_result(*&stash, ft_strchr(*stash, '\n')));
}

char	*get_next_line(int fd)
{
	static char		*stash = NULL;

	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0)
	{
		free (stash);
		stash = NULL;
		return (NULL);
	}
	if (stash == NULL)
		stash = ft_strdup("");
	if (stash != NULL && ft_strchr(stash, '\n') != NULL)
		return (get_result(&stash, ft_strchr(stash, '\n')));
	return (read_and_add_line_to_stash(&stash, fd));
}
