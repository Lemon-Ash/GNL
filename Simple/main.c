/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboza-ba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 13:41:49 by lboza-ba          #+#    #+#             */
/*   Updated: 2019/11/28 11:52:58 by lboza-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int		main(void)
{
	char	*line = 0;
 	int		fd;
	int		mark;

	mark = 1;

	fd = open("big_file", O_RDONLY);
	while (mark > 0)
	{
	mark = get_next_line(fd, &line);
	printf("| %s\n", line);
	}
}
