/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboza-ba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:40:24 by lboza-ba          #+#    #+#             */
/*   Updated: 2019/11/28 12:06:07 by lboza-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>

int	get_next_line(int fd, char **line) 
{
	char	data;
	int		readed;
	int		i;

	*line = (char*)malloc(100 * sizeof(char));
	i = 0;
	data = ' ';
	while (data != '\n')
	{
		readed = read(fd, &data, 1);
		//printf("El caracter leído es: %c\n", data);
		//printf("El valor de readed es: %d\n", readed);
		if(readed < 0)
		{
			//write(2, "An error occurred in the read.\n", 31);
			return (-1) ;
		}
		else if (readed == 0)
		{
			(*line)[i] = '\0';
		//	write(1, "End of file reached\n", 20);
			return (0) ;
		}
		else if (data == '\n')
			break ;
		(*line)[i++] = data;
		//printf("El caracter copiado es: %c\n", (*line)[i - 1]);
	}
	(*line)[i] = '\0';
	return (1);
}
