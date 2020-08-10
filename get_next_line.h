/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboza-ba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:50:55 by lboza-ba          #+#    #+#             */
/*   Updated: 2020/08/09 19:43:40 by lboza-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

int					get_next_line(int fd, char **line);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
typedef	struct		s_buff_file {
	int					fd;
	char				*buf;
	struct s_buff_file	*next;
}				t_file;
struct s_buff_file	*ft_freelist(t_file *reading, t_file *now_reading);

#endif
