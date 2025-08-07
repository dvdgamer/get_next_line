/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   get_next_line_bonus_utils.c                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: dponte <dponte@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/08/07 11:39:53 by dponte       #+#    #+#                  */
/*   Updated: 2025/08/07 11:42:11 by dponte       ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char *get_next_line(int fd) {
    return get_next_line_bonus(fd);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*returned_str;
	size_t	i;
	size_t	len;

	len = ft_strlen(s);
	returned_str = malloc(len + 1);
	if (!returned_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		returned_str[i] = s[i];
		i++;
	}
	returned_str[i] = '\0';
	return (returned_str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*return_string;

	if (ft_strlen(s1) + ft_strlen(s2) < 1)
		return (ft_strdup(""));
	return_string = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!return_string)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		return_string[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < ft_strlen(s2))
	{
		return_string[ft_strlen(s1) + i] = s2[i];
		i++;
	}
	return_string[ft_strlen(s1) + i] = '\0';
	return (return_string);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	byte;

	ptr = (unsigned char *)s;
	byte = (unsigned char)c;
	while (n--)
		*ptr++ = byte;
	return (s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*substr;

	s_len = ft_strlen(s);
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	substr = malloc(len + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i] != '\0')
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
