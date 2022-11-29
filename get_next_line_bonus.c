/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 02:28:25 by lfiorini          #+#    #+#             */
/*   Updated: 2022/11/29 18:40:55 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static t_string	init_string(void)
{
	t_string	s;

	s.str = 0;
	s.len = 0;
	s.size = 0;
	return (s);
}

static t_buffer	*get_buffer(int fd, t_buffer *b)
{
	while (1)
	{
		if (b->fd == fd)
			return (b);
		else if (b->next)
			b = b->next;
		else
		{
			b->next = (t_buffer *) malloc(sizeof(t_buffer));
			if (!b->next)
				return (0);
			b = b->next;
			b->fd = fd;
			b->idx = 0;
			b->len = 0;
			b->next = 0;
		}
	}
}

static int	delete_buffer(int fd, t_buffer *b)
{
	t_buffer	*cur;
	t_buffer	*temp;

	cur = b;
	while (cur->next)
	{
		if (cur->next->fd == fd)
		{
			temp = cur->next->next;
			free(cur->next);
			cur->next = temp;
			return (1);
		}
		else
			cur = cur->next;
	}
	return (0);
}

static int	loop(int fd, t_buffer *cur, t_string *line)
{
	while (1)
	{
		if (!cur->idx)
			cur->len = read(fd, cur->buf, BUFFER_SIZE);
		if (cur->len <= 0 || !update_line(line, *cur))
			break ;
		cur->idx = (get_index(cur->buf, '\n', cur->idx, cur->len) + 1);
		cur->idx %= cur->len;
		if (line->str[line->len - 1] == '\n' || cur->idx)
			break ;
	}
	*line = optimize_string(*line);
	if (cur->len == -1)
	{
		free(line->str);
		line->str = 0;
	}
	if ((cur->len < BUFFER_SIZE && !cur->idx) || !line->str)
		return (1);
	return (0);
}

char	*get_next_line(int fd)
{
	static t_buffer	head;
	t_buffer		*cur;
	t_string		line;

	cur = get_buffer(fd, &head);
	if (!cur)
		return (0);
	line = init_string();
	if (loop(fd, cur, &line))
		delete_buffer(fd, &head);
	return (line.str);
}
