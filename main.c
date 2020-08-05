/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboza-ba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 13:41:49 by lboza-ba          #+#    #+#             */
/*   Updated: 2020/08/05 21:46:01 by lboza-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int		main(void)
{
	char	*line;
 	int		fd1;
	int 	fd2;
	int	mark;

	mark = 1;
	fd1 = open("big_file", O_RDONLY);
	fd2 = open("big_file2", O_RDONLY);
	if (fd1 > 0 && fd2 > 0)
		write(1, "Ha abierto los archivos\n", 24);
	while (mark > 0)
	{
	mark = get_next_line(fd1, &line);
	printf("| %s\n", line);
	mark = get_next_line(fd2, &line);
	printf("| %s\n", line);
	/*mark = get_next_line(fd1, &line);
	printf("| %s\n", line);
	mark = get_next_line(fd2, &line);
	printf("| %s\n", line);*/
	}
}
