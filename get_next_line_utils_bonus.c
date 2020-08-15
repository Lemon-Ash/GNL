/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboza-ba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:53:47 by lboza-ba          #+#    #+#             */
/*   Updated: 2020/08/15 12:51:37 by lboza-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

void	*ft_freelist(t_file *reading, t_file *now_reading)
{
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
			return (0);
	}
	free((void*)now_reading->buf);
	free(now_reading);
	return (0);
}
