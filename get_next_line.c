/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboza-ba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:40:24 by lboza-ba          #+#    #+#             */
/*   Updated: 2020/08/07 22:11:14 by lboza-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/*void	*ft_memmove(void *dst, const void *src, size_t len)
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
 }*/

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	char	*new;
	char	*init_new;

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
	init_new = new;
	while (*s1 != '\0')
		*new++ = *s1++;
	while (*s2 != '\0')
		*new++ = *s2++;
	*new = '\0';
	//if(*s1 != '\0')
	//	free((void*)s1);
	return (init_new);
}

int get_line (file *now_red, char **line)
{
	int i;
	char *mo;
	char *buf;
	char *line2;

	line2 = *line;
	buf = now_red->buf;
	i = 0;
	if (buf == NULL)
	{
		return (-1);
	}
	if(!(mo = (char*)malloc(BUFFER_SIZE + 1 * sizeof(char))))
		return (-1);
	while (*buf != '\n' && *buf != '\0')
	{
		mo[i++] = *buf++;
	}
	mo[i] = '\0';
	*line = ft_strjoin(*line, mo);
	//printf("La direccion de memoria de *line despues de join es: %p\n", *line);
	if (*line2 != '\0')
		free(line2);
	free(mo);
	i = 0;
	if (*buf == '\0')
	{
		free((void*)now_red->buf);
		return (0);
	}
	else
	{
		buf++;
		ft_strlcpy(&(now_red->buf[0]), &(*buf),  BUFFER_SIZE);
		return (1);
	}
}

int	get_buffer_line(file *now_reading, char **line) 
{
	int		end_line;
	int		readed;
	int		i;

	end_line = 0;

	while (end_line == 0)
	{		
		if (!(now_reading->buf = (char*)malloc((BUFFER_SIZE + 1) * sizeof(char))))
			return(-1);
		i = 0;
		while(i <= BUFFER_SIZE)
			now_reading->buf[i++] = '\0';
		readed = read(now_reading->fd, now_reading->buf, BUFFER_SIZE);
		if(readed < 0)
		{
			//	write(2, "An error occurred in the read.\n", 31);
			return (-1) ;
		}
		else if (readed == 0)
		{
			//write(1, "End of file reached\n", 20);
			return (0) ;
		}
		else
		{
			end_line = get_line(now_reading, line);
		}
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
	return now_reading;
}

int get_next_line(int fd, char **line) 
{
	static file	*reading;
	int			returning;
	file		*now_red; 

	if (line == NULL)
		return(-1);
	if (reading == NULL)
	{
		if (!(reading = (file*)malloc(1 * sizeof(file))))
			return (-1);
		reading->fd = fd;
		reading->buf = NULL;
		reading->next = NULL;
	}
	*line = "";
	returning = 1;
	now_red = get_fd(fd, reading);
	if (get_line(now_red, line) != 1)
	{
		returning = get_buffer_line(now_red, line);
	}
	return (returning);
}
