/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   get_next_line.c                                   :+:    :+:             */
/*                                                    +:+                     */
/*   By: dponte <dponte@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/07/01 14:31:50 by dponte       #+#    #+#                  */
/*   Updated: 2025/07/05 12:33:19 by dponte       ########   odam.nl          */
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

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			total_size;
	size_t			i;

	if (size && count > SIZE_MAX / size)
		return (NULL);
	total_size = count * size;
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < total_size)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

char	*get_result(char **stash, char *line_break)
{
	size_t		len;
	char		*result;

	len = (line_break + 1) - *stash;
	result = ft_substr(*stash, 0, len);
	*stash = ft_strdup(line_break + 1);
	return (result);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*result;
	char		*line_break;
	static char	*stash = NULL;
	size_t		byte_count;

	buffer = ft_calloc(BUFFER_SIZE, sizeof(char));
	line_break = NULL;
	if (stash == NULL)
		stash = ft_strdup("");
	else
	{
		if (ft_strchr(stash, '\n') != NULL)
		{
			line_break = ft_strchr(stash, '\n');
			return (get_result(&stash, line_break));
		}
	}
	while (line_break == NULL)
	{
		byte_count = read(fd, buffer, BUFFER_SIZE);
		stash = ft_strjoin(stash, buffer);
		line_break = ft_strchr(stash, '\n');
	}
	return (get_result(&stash, line_break));
}
