/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboza-ba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:40:24 by lboza-ba          #+#    #+#             */
/*   Updated: 2019/12/18 15:13:58 by lboza-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*ptr;
	const unsigned char	*ptr2;

	ptr = (unsigned char*)dst;
	ptr2 = (unsigned char*)src;
	i = 0;
	if (dst == src)
		return (dst);
	if (ptr2 < ptr)
		while (++i <= len)
			ptr[len - i] = ptr2[len - i];
	else
		while (len-- > 0)
			*(ptr++) = *(ptr2++);
	return (dst);
}	

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t dst_len;
	size_t count;

	dst_len = 0;
	count = 0;
	while (dst[count] && dstsize > count)
		count++;
	dst_len = count;
	while (src[count - dst_len] && count + 1 < dstsize)
	{
		dst[count] = src[count - dst_len];
		count++;
	}
	if (dst_len < dstsize)
		dst[count] = '\0';
	return (dst_len + ft_strlen(src));
}

int get_line (file *now_red, char *line)
{
	int i;
	int length;
	char *mo;
	char *buf;

	if(!(mo = (char*)malloc(BUFFER_SIZE * sizeof(char))))
		return (-1);
	buf = now_red->buf;
	i = 0;
	if (buf == NULL)
		return (-1);
	printf("El contenido de line antes es: %s\n", mo);
	while (*buf != '\n' && *buf != '\0')
	{
		mo[i++] = *buf++;
	}
	length = strlen(line);
	length += strlen (mo);
	ft_strlcat(line, mo, length);
	printf("El contenido de line después es: %s\n", line);
	printf("El contenido de mo después es: %s\n", mo);
	free(mo);
	if (*buf == '\0')
		return (0);
	else
	{
		buf++;
		//*line = '\0';
		now_red->buf = ft_memmove(&(*buf), &(buf[0]),  BUFFER_SIZE);
		printf("El contenido de buf después del salto es: %s\n", now_red->buf);
		return (1);
	}
}

int	get_buffer_line(file *now_reading, char **line) 
{
	int		end_line;
	int		readed;

	now_reading->buf = (char*)malloc((BUFFER_SIZE + 1) * sizeof(char));
	end_line = 0;
	while (end_line == 0)
	{
		readed = read(now_reading->fd, now_reading->buf, BUFFER_SIZE);
		printf("El contenido leido de now_reading->buf es: %s\n", now_reading->buf);
		if(readed < 0)
		{
			write(2, "An error occurred in the read.\n", 31);
			return (-1) ;
		}
		else if (readed == 0)
		{
			//write(1, "End of file reached\n", 20);
			return (0) ;
		}
		else
			end_line = get_line(now_reading, *line);
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
			now_reading->next = new_file;
			now_reading = now_reading->next;
			printf("Ha entrado aqui\n");
		}
	}
	else
		now_reading->fd = fd;
	printf("El valor 1 de now_reading.fd es: %d\n",now_reading->fd);
	return now_reading;
}

int get_next_line(int fd, char **line) 
{
	static file	*reading;
	int			returning;
	file		*now_red;
	file		*red;
	char		*line2;


	if (!(*line = (char*)malloc(1 * sizeof(char))))
		return (-1);
	line2 = *line;

	if (reading == NULL)
	{
		if (!(reading = (file*)malloc(1 * sizeof(file))))
			return (-1);
		reading->fd = fd;
		reading->buf = NULL;
		reading->next = NULL;
		printf("ha creado un nuevo nodo\n");
	}
	returning = 1;
	if (!(red = (file*)malloc(1 * sizeof(file))))
		return (-1);
	red = reading;

	printf("El valor de reading.fd es: %d\n", reading->fd);
	printf("El valor de reading.buf es: %s\n", reading->buf);
	now_red = get_fd(fd, red);
	printf("El valor de reading.fd es: %d\n", reading->fd);
	printf("El valor de reading.buf es: %s\n", reading->buf);
	printf("El contenido de buf al principio es: %s\n", now_red->buf);
	if (get_line(now_red, *line) != 1)
		returning = get_buffer_line(now_red, line);
	printf("El contenido de line al final es: %s\n", line2);
	printf("El contenido de buf al final es: %s\n", now_red->buf);
	printf("El valor guardado de reading.fd es: %d\n", reading->fd);
	printf("El valor guardado de reading.buf es: %s\n", reading->buf);
	free(red);
	return (returning);
}
