/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboza-ba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:40:24 by lboza-ba          #+#    #+#             */
/*   Updated: 2020/08/16 18:04:07 by lboza-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char				*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	char	*new;

	if (s1 == 0 || s2 == 0)
		return (0);
	s1_len = 0;
	s2_len = 0;
	while (*(s1 + s1_len) != '\0')
		s1_len++;
	while (*(s2 + s2_len) != '\0')
		s2_len++;
	if (!(new = malloc((s1_len + s2_len + 1) * sizeof(char))))
		return (0);
	while (*s1 != '\0')
		*new++ = *s1++;
	while (*s2 != '\0')
		*new++ = *s2++;
	*new = '\0';
	s1 -= s1_len;
	free((void*)s1);
	new -= (s1_len + s2_len);
	return (new);
}

int					get_line(t_file *now_read, char **line)
{
	int		i;
	char	*mo;
	char	*buf;

	i = 0;
	buf = now_read->buf;
	if (*buf == '\0')
		return (-1);
	if (!(mo = (char*)malloc(BUFFER_SIZE + 1 * sizeof(char))))
		return (-1);
	while (*buf != '\n' && *buf != '\0')
		*(mo + i++) = *buf++;
	*(mo + i) = '\0';
	*line = ft_strjoin(*line, mo);
	free(mo);
	if (*buf == '\0')
	{
		while (0 <= i)
			*(now_read->buf + i--) = '\0';
		return (0);
	}
	ft_strlcpy(now_read->buf, ++buf, BUFFER_SIZE);
	return (1);
}

int					get_buffer_line(t_file *now_read, char **line)
{
	int		end_line;
	int		readed;

	end_line = 0;
	while (end_line == 0)
	{
		*(now_read->buf + BUFFER_SIZE) = '\0';
		readed = read(now_read->fd, now_read->buf, BUFFER_SIZE);
		if (readed < 0)
		{
			*line = NULL;
			return (-1);
		}
		else if (readed == 0)
			return (0);
		else
			end_line = get_line(now_read, line);
	}
	return (1);
}

struct s_buff_file	*get_fd(int fd, t_file *now_reading)
{
	t_file	*new_file;

	if (now_reading)
		while (now_reading->fd != fd && now_reading->next)
			now_reading = now_reading->next;
	if ((!now_reading) || now_reading->fd != fd)
	{
		if (!(new_file = (t_file*)malloc(1 * sizeof(t_file))))
			return (NULL);
		if (!(new_file->buf = (char*)malloc((BUFFER_SIZE + 1) * sizeof(char))))
			return (NULL);
		new_file->fd = fd;
		*(new_file->buf) = '\0';
		new_file->next = 0;
		if (now_reading)
			now_reading->next = new_file;
		now_reading = new_file;
	}
	return (now_reading);
}

int					get_next_line(int fd, char **line)
{
	static t_file	*reading;
	int				returning;
	t_file			*now_read;

	if (line == NULL || BUFFER_SIZE < 1 || read(fd, NULL, 0) == -1)
		return (-1);
	if (!(*line = (char*)malloc(1 * sizeof(char))))
		return (-1);
	**line = '\0';
	returning = 1;
	now_read = get_fd(fd, reading);
	if (!reading)
		reading = now_read;
	if (get_line(now_read, line) != 1)
		returning = get_buffer_line(now_read, line);
	if (returning <= 0)
		ft_freelist(&reading, now_read);
	return (returning);
}
