/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboza-ba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:53:47 by lboza-ba          #+#    #+#             */
/*   Updated: 2020/08/16 14:44:53 by lboza-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "stdio.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int cont;

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

int		ft_freelist(t_file *reading, t_file *now_reading)
{
	int last;

	last = 0;
	if (reading->fd != now_reading->fd)
	{
		while ((reading->next)->fd != now_reading->fd)
			reading = reading->next;
		reading->next = now_reading->next;
	}
	else
	{
		if (reading->next != NULL)
			reading = reading->next;
		else
			last = 1;
	}	
	free((void*)now_reading->buf);
	free(now_reading);
	return (last);
}
