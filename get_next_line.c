/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 03:26:34 by lfiorini          #+#    #+#             */
/*   Updated: 2022/11/29 17:47:44 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_string	init_string(void)
{
	t_string	s;

	s.str = 0;
	s.len = 0;
	s.size = 0;
	return (s);
}

static int	read_buffer(int fd, t_buffer *b)
{
	b->len = read(fd, b->buf, BUFFER_SIZE);
	if (b->len > 0)
		return (1);
	return (0);
}

char	*get_next_line(int fd)
{
	static t_buffer	buffer;
	t_string		line;

	line = init_string();
	while (1)
	{
		if (!buffer.idx && !read_buffer(fd, &buffer))
			break ;
		if (!update_line(&line, buffer) || !update_buffer(&buffer))
			break ;
		if (line.str[line.len - 1] == '\n' || buffer.idx)
			break ;
	}
	if (buffer.len == -1)
		return (free(line.str), NULL);
	line = optimize_string(line);
	return (line.str);
}
