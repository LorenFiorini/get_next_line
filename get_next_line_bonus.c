/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 02:28:25 by lfiorini          #+#    #+#             */
/*   Updated: 2022/11/28 02:36:12 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

char	*read_buffer(int fd, char *sp)
{
	char	*b;
	int		i;

	i = BUFFER_SIZE;
	b = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!b)
		return (NULL);
	while (i == BUFFER_SIZE && (!ft_strchr(sp, '\n')))
	{
		i = read(fd, b, BUFFER_SIZE);
		if (i == 0)
			break ;
		if (i == -1)
			return (free(sp), free(b), NULL);
		b[i] = '\0';
		sp = ft_strjoin_free(sp, b);
		if (!*sp || !sp)
			return (free(sp), free(b), NULL);
	}
	free(b);
	return (sp);
}

char	*getting_line(char *sp)
{
	char	*line;
	int		i;

	i = 0;
	if (!sp)
		return (free(sp), NULL);
	while (sp[i] != '\n' && sp[i] != '\0')
		i++;
	if (sp[i] == '\n')
		i++;
	line = (char *)ft_calloc(i + 1, sizeof(char));
	if (!line)
		return (free(sp), NULL);
	line[i] = '\0';
	while (i > 0)
	{
		i--;
		line[i] = sp[i];
	}
	return (line);
}

char	*remaining(char *sp)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!sp)
		return (free(sp), NULL);
	while (sp[i] != '\n' && sp[i] != '\0')
		i++;
	if (sp[i] == '\0' || sp[i + 1] == '\0')
		return (free(sp), NULL);
	new = (char *)ft_calloc(ft_strlen(sp) - i + 1, sizeof(char));
	if (!new)
		return (free(sp), NULL);
	i++;
	while (sp[i] != '\0')
		new[j++] = sp[i++];
	new[j] = '\0';
	free(sp);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*sp[MAX_FD];
	char		*ln;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	sp[fd] = read_buffer(fd, sp[fd]);
	ln = getting_line(sp[fd]);
	sp[fd] = remaining(sp[fd]);
	return (ln);
}
