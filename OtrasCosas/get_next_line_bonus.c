/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboza-ba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:40:24 by lboza-ba          #+#    #+#             */
/*   Updated: 2020/08/12 20:22:01 by lboza-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

int					get_line(char* buffer, char **line)
{
	int		i;
	char	*mo;
	char	*buf;

	i = 0;
	buf = buffer;
	if (buf ==NULL || *buf == '\0')
		return (-1);
	if (!(mo = (char*)malloc(BUFFER_SIZE + 1 * sizeof(char))))
		return (-1);
	while (*buf != '\n' && *buf != '\0')
		*(mo + i++) = *buf++;
	*(mo + i) = '\0';
	*line = ft_strjoin(*line, mo);
	free(mo);
	i = 0;
	if (*buf == '\0')
	{
		while (0 <= i)
			*(buffer + i--) = '\0';
		return (0);
	}
	ft_strlcpy(buffer, ++buf, BUFFER_SIZE);
	return (1);
}

int					get_buffer_line(int fd, char *buffer, char **line)
{
	int		end_line;
	int		readed;

	end_line = 0;
	while (end_line == 0)
	{
		//buffer[BUFFER_SIZE] = '\0';
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed < 0)
		{
			*line = NULL;
			return (-1);
		}
		else if (readed == 0)
			return (0);
		else
			end_line = get_line(buffer, line);
	}
	return (1);
}

int					get_next_line(int fd, char **line)
{
	static char	lr[258][BUFFER_SIZE + 1];
	int			returning;
	int 		i;

	i = 0;
	if (fd < 0 || line == NULL || BUFFER_SIZE < 1 || read(fd, NULL, 0) == -1)
		return (-1);
	if (lr[fd] == NULL)
	{
		while (i <= BUFFER_SIZE)
			*(lr[fd] + i++) = '\0';
	}
	if (!(*line = (char*)malloc(1 * sizeof(char))))
		return (-1);
	**line = '\0';
	returning = 1;
	if (get_line(lr[fd], line) != 1)
		returning = get_buffer_line(fd, lr[fd], line);
	return (returning);
}
