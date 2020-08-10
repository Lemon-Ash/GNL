/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnavarre <rnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 12:22:12 by rnavarre          #+#    #+#             */
/*   Updated: 2020/08/10 12:28:51 by rnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

int		getchrlen(int *found, char *str, char c)
{
	int	i;

	i = 0;
	*found = 1;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	*found = 0;
	return (i);
}

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ft_strcat(char *str1, char *str2)
{
	char	*out;
	int		i;
	int		str1len;
	int		str2len;

	str1len = ft_strlen(str1);
	str2len = ft_strlen(str2);
	if (!(out = (char *)malloc(sizeof(char) * (str1len + str2len + 1))))
		return (NULL);
	i = 0;
	while (i < str1len)
	{
		out[i] = str1[i];
		i++;
	}
	while (i - str1len < str2len)
	{
		out[i] = str2[i - str1len];
		i++;
	}
	out[i] = '\0';
	return (out);
}
