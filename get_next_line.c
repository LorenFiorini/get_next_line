/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:00:47 by lfiorini          #+#    #+#             */
/*   Updated: 2022/11/25 20:21:46 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*read_buffer(int fd, char *ptr, int *flag)
{
	char	*b;
	int		i;

	i = 1;
	b = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!b)
		return (NULL);
	while (i > 0 && ft_strchr(ptr, '\n') == NULL)
	{
		i = read(fd, b, BUFFER_SIZE);
		if (i == -1)
			return (free(b), free(ptr), NULL);
		b[i] = '\0';
		if (!ptr)
			ptr = ft_strdup(b);
		else
			ptr = ft_strjoin(ptr, b);
	}
	*flag = i;
	free(b);
	return (ptr);
}

char	*ft_get_line(char *sptr)
{
	char	*line;
	int		line_len;

	line_len = 0;
	if (!*sptr)
	{
		free (sptr);
		return (NULL);
	}
	while ((sptr[line_len] != '\n' && sptr[line_len] != '\0'))
		line_len++;
	line = ft_substr(sptr, 0, line_len + 1);
	return (line);
}

char	*remain_part(char *sptr, int flag)
{
	char	*ptr;
	size_t	len;
	size_t	len_line;

	ptr = NULL;
	if (!*sptr)
	{
		free(sptr);
		return (NULL);
	}
	len = ft_strlen(sptr);
	len_line = ft_strchr(sptr, '\n') - sptr + 1;
	if (flag != 0)
		ptr = ft_substr(sptr, len_line, len - len_line);
	free(sptr);
	return (ptr);
}

char	*get_next_line(int fd)
{
	static char	*sp = NULL;
	char		*ln;
	int			flag;

	flag = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	sp = read_buffer(fd, sp, &flag);
	if (!sp)
		return (NULL);
	if (*sp)
		ln = ft_get_line(sp);
	else
		ln = (NULL);
	sp = remain_part(sp, flag);
	return (ln);
}
