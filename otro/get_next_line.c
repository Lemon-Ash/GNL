/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnavarre <rnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 12:21:46 by rnavarre          #+#    #+#             */
/*   Updated: 2020/08/10 12:28:48 by rnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

static char	*readbuffer(int *found, char *buffer, char c)
{
	int		i;
	int		len;
	char	*out;

	i = 0;
	len = getchrlen(found, buffer, c);
	if (!(out = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	out[len] = '\0';
	while (i < len)
	{
		out[i] = buffer[i];
		i++;
	}
	if (i < BUFFER_SIZE)
	{
		while (buffer[i + 1])
		{
			buffer[i - len] = buffer[i + 1];
			i++;
		}
		buffer[i - len] = '\0';
	}
	return (out);
}

int			get_next_line(int fd, char **line)
{
	static char	buffer[BUFFER_SIZE + 1];
	int			status;
	char		*prev;
	char		*out;

	prev = NULL;
	status = 0;
	while (fd >= 0 && line && read(fd, NULL, 0) != -1 && BUFFER_SIZE > 0)
	{
		if (!((out) = readbuffer(&status, buffer, '\n')))
			break ;
		if (!((*line) = ft_strcat(prev, out)))
			break ;
		free(out);
		free(prev);
		if (status)
			return (1);
		if ((status = read(fd, buffer, BUFFER_SIZE)) != -1)
			buffer[status] = '\0';
		if (!status)
			return (0);
		prev = *line;
	}
	return (-1);
}
