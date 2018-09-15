/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 20:54:33 by mjacques          #+#    #+#             */
/*   Updated: 2018/09/14 16:36:46 by fhong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

int		get_next_line(const int fd, char **line)
{
	t_gnl		var;
	static char *str[FDS];

	ft_memset(var.buff, 0, BUFF_SIZE);
	if (fd < 0 || fd > FDS || !line || (var.size = read(fd, var.buff, 1)) < 0)
		return (-1);
	!str[fd] ? str[fd] = ft_strnew(0) : 0;
	if (var.size == 0 && !(ft_strchr(str[fd], '\n'))
		&& ft_strlen(str[fd]) < 1)
		return (0);
	str[fd] = ft_strappend(str[fd], var.buff[0]);
	while (!(var.pos = ft_strchr(str[fd], '\n'))
		&& (var.size = read(fd, var.buff, BUFF_SIZE)))
	{
		var.buff[var.size] = '\0';
		str[fd] = ft_strjoin(str[fd], var.buff);
	}
	var.size = (int)(var.pos - str[fd]);
	(!var.pos) ? (var.size = ft_strlen(str[fd])) : 0;
	*line = ft_strlcpy(str[fd], var.size);
	(var.pos) ? (var.size += 1) : 0;
	var.tmp = ft_strdup(&str[fd][var.size]);
	ft_strdel(&str[fd]);
	str[fd] = var.tmp;
	return (1);
}
