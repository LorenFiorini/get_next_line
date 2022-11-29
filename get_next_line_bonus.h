/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorini <lfiorini@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 02:28:31 by lfiorini          #+#    #+#             */
/*   Updated: 2022/11/29 19:16:48 by lfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef MAX_FD
#  define MAX_FD 8192
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

t_string	init_string(void);
int			get_index(char *s, char c, int begin, int end);
int			update_line(t_string *l, t_buffer b);
t_string	optimize_string(t_string s);
void		*gnl_memcpy(void *dst, const void *src, size_t n);

char		*get_next_line(int fd);

#endif
