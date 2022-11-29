/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 02:28:31 by lfiorini          #+#    #+#             */
/*   Updated: 2022/11/29 18:40:53 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_buffer	t_buffer;

typedef struct s_buffer
{
	int			fd;
	char		buf[BUFFER_SIZE];
	int			idx;
	int			len;
	t_buffer	*next;
}	t_buffer;

typedef struct s_string
{
	char	*str;
	int		len;
	int		size;
}	t_string;

int			get_index(char *s, char c, int begin, int end);
int			update_line(t_string *l, t_buffer b);
int			update_buffer(t_buffer *b);
t_string	optimize_string(t_string s);

char		*get_next_line(int fd);

#endif
