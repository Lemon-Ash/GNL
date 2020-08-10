/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboza-ba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 13:41:49 by lboza-ba          #+#    #+#             */
/*   Updated: 2020/08/10 18:39:13 by lboza-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"


int	main(int argc, char **argv)
{
	int		i;
	int		fd;
	int		status;
	char	*line;
	
	if (argc == 1)
			fd = 0;
	i = 1;
//	while (i < argc)
//	{
		fd = open("big_file", O_RDONLY);
		//printf("Comienza lectura %s:\n", argv[i]);

		while ((status = get_next_line(fd, &line)) > 0)
		{
			printf("> %s\n", line);
			free(line);
		}
		if (status == 0)
		{
			printf("! %s\n", line);
			free(line);
		}
		if (status == -1)
			printf("Ha ocurrido un error al intentar leer el archivo %s.\n", argv[i]);
		if (status == 0)
			printf("-\n");
		i++;
//	}
	return (0);
}
