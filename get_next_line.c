/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboza-ba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:40:24 by lboza-ba          #+#    #+#             */
/*   Updated: 2020/08/09 22:43:09 by lboza-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "stdio.h"

size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int cont;

	cont = 0;
	if (!dst || !src)
		return(0);
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

int					get_line(char *buffer, char **line)
{
	int		i;
	char	*mo;
	char	*buf;

	i = 0;
	buf = buffer;
	if (buffer == NULL)
		return (-1);
	if (!(mo = (char*)malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (-1);
	while (*buf != '\n' && *buf != '\0')
		*(mo+i++) = *buf++;
	*(mo+i) = '\0';
	printf("El contenido de line antes de strjoin es: %s\n", *line);
	*line = ft_strjoin(*line, mo);
	printf("El contenido de line despues de strjoin es: %s\n", *line);
	free(mo);
	if (*buf == '\0')
	{
		free((void*)buffer);
		return (0);
	}
	else
	{
		printf("El buffer antes del strlcpy es: %s\n", buffer);
		ft_strlcpy(buffer, ++buf, BUFFER_SIZE);
		printf("El buffer despues del strlcpy es: %s\n", buffer);
		return (1);
	}
}

int					get_buffer_line(int fd, char *buffer, char **line)
{
	int		end_line;
	int		readed;
	int		i;

	i = 0;
	end_line = 0;
	while (end_line == 0)
	{
		if (!(buffer = (char*)malloc((BUFFER_SIZE + 1) * sizeof(char))))
			return (-1);
		while (i <=BUFFER_SIZE)
			buffer[i++] = '\0';
		readed = read(fd, buffer, BUFFER_SIZE);
		printf("El contenido de buffer después de leer es: %s\n", buffer);
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
	static char	*buffer;
	int			returning;

	if (line == NULL || BUFFER_SIZE < 1)
		return (-1);
	if (!(*line = (char*)malloc(1 * sizeof(char))))
		return (-1);
	**line = '\0';
	returning = 1;
	if (get_line(buffer, line) != 1)
		returning = get_buffer_line(fd, buffer, line);
	if (returning < 1)
		free(buffer);
	return (returning);
}
