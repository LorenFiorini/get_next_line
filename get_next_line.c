/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 03:26:34 by lfiorini          #+#    #+#             */
/*   Updated: 2022/11/29 18:54:02 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_buffer	buffer;
	t_string		line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = init_string();
	while (1)
	{
		if (!buffer.idx)
			buffer.len = read(fd, buffer.buf, BUFFER_SIZE);
		if (buffer.len <= 0)
			break ;
		if (!update_line(&line, buffer))
			break ;
		buffer.idx = get_index(buffer.buf, '\n', buffer.idx, buffer.len);
		buffer.idx = (buffer.idx + 1) % buffer.len;
		if (line.str[line.len - 1] == '\n' || buffer.idx)
			break ;
	}
	if (buffer.len == -1)
		return (free(line.str), NULL);
	line = optimize_string(line);
	return (line.str);
}
