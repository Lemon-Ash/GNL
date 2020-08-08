/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboza-ba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:40:24 by lboza-ba          #+#    #+#             */
/*   Updated: 2020/08/08 18:57:24 by lboza-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int	cont;

	cont = 0;
	if (!dst || !src)
		return (0);
	while (src[cont] != '\0')
		cont++;
	while (dstsize > 1 && *src != '\0')
	{
		*dst = *src;
		dst++;
		src++;
		dstsize--;
	}
	if (dstsize != 0)
		*dst = '\0';
	return (cont);
}

char				*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	char	*new;

	if (s1 == 0 || s2 == 0)
		return (0);
	s1_len = 0;
	s2_len = 0;
	while (*s1++ != '\0')
		s1_len++;
	s1 -= (s1_len + 1);
	while (*s2++ != '\0')
		s2_len++;
	s2 -= (s2_len + 1);
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

int					get_line(file *now_red, char **line)
{
	int		i;
	char	*mo;
	char	*buf;

	i = 0;
	buf = now_red->buf;
	if (buf == NULL)
		return (-1);
	if (!(mo = (char*)malloc(BUFFER_SIZE + 1 * sizeof(char))))
		return (-1);
	while (*buf != '\n' && *buf != '\0')
		mo[i++] = *buf++;
	mo[i] = '\0';
	*line = ft_strjoin(*line, mo);
	free(mo);
	if (*buf == '\0')
	{
		free((void*)now_red->buf);
		return (0);
	}
	else
	{
		ft_strlcpy(&(now_red->buf[0]), &(*(++buf)), BUFFER_SIZE);
		return (1);
	}
}

int					get_buffer_line(file *now_read, char **line)
{
	int		end_line;
	int		readed;
	int		i;

	end_line = 0;
	while (end_line == 0)
	{
		if (!(now_read->buf = (char*)malloc((BUFFER_SIZE + 1) * sizeof(char))))
			return (-1);
		i = 0;
		while (i <= BUFFER_SIZE)
			now_read->buf[i++] = '\0';
		readed = read(now_read->fd, now_read->buf, BUFFER_SIZE);
		if (readed < 0)
			return (-1);
		else if (readed == 0)
			return (0);
		else
			end_line = get_line(now_read, line);
	}
	return (1);
}

struct buff_file	*get_fd(int fd, file *now_reading)
{
	file	*new_file;

	if (now_reading->fd != 0)
	{
		while (now_reading->fd != fd && now_reading->next != NULL)
			now_reading = now_reading->next;
		if (now_reading->fd != fd)
		{
			if (!(new_file = (file*)malloc(1 * sizeof(file))))
				return (new_file = NULL);
			new_file->fd = fd;
			new_file->buf = NULL;
			new_file->next = NULL;
			now_reading->next = new_file;
			now_reading = now_reading->next;
		}
	}
	else
		now_reading->fd = fd;
	return (now_reading);
}

int					get_next_line(int fd, char **line)
{
	static file	*reading;
	int			returning;
	file		*now_red;

	if (line == NULL ||BUFFER_SIZE < 1)
		return (-1);
	if (BUFFER_SIZE == 0)
		return (-1);
	if (reading == NULL)
	{
		if (!(reading = (file*)malloc(1 * sizeof(file))))
			return (-1);
		reading->fd = fd;
		reading->buf = NULL;
		reading->next = NULL;
	}
	if (!(*line = (char*)malloc(1 * sizeof(char))))
		return (-1);
	**line = '\0';
	returning = 1;
	now_red = get_fd(fd, reading);
	if (get_line(now_red, line) != 1)
	{
		returning = get_buffer_line(now_red, line);
	}
	return (returning);
}
