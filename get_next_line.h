/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboza-ba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:50:55 by lboza-ba          #+#    #+#             */
/*   Updated: 2019/12/12 15:05:28 by lboza-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//#ifndef	GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
#ifndef	BUFF_SIZE
# define BUFF_SIZE 20
# include <stdlib.h>
# include <unistd.h>

int		get_next_line(int fd, char **line);

typedef	struct buff_file {
	int					fd;
	char				*buf;
	struct buff_file	*next;
}				file;

#endif
