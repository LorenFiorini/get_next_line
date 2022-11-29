/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 02:28:25 by lfiorini          #+#    #+#             */
/*   Updated: 2022/11/29 19:17:20 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_buffer	buf[MAX_FD];
	t_string		line;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	line = init_string();
	while (1)
	{
		if (!buf[fd].idx)
			buf[fd].len = read(fd, buf[fd].buf, BUFFER_SIZE);
		if (buf[fd].len <= 0)
			break ;
		if (!update_line(&line, buf[fd]))
			break ;
		buf[fd].idx = get_index(buf[fd].buf, '\n', buf[fd].idx, buf[fd].len);
		buf[fd].idx = (buf[fd].idx + 1) % buf[fd].len;
		if (line.str[line.len - 1] == '\n' || buf[fd].idx)
			break ;
	}
	if (buf[fd].len == -1)
		return (free(line.str), NULL);
	line = optimize_string(line);
	return (line.str);
}
