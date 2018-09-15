/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 18:17:28 by mjacques          #+#    #+#             */
/*   Updated: 2018/09/14 16:34:57 by fhong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

int		main(int argc, char *argv[])
{
	int		openfile;
	char	*tmp;

	openfile = 0;
	if (argc == 2)
	{
		if (!(tmp = ft_strrchr(argv[1], '.')) || ft_strcmp(tmp, ".s") != 0)
			ft_error("ERROR: Invalid file extension");
		else if ((openfile = open(argv[1], O_RDONLY)) > 0)
			addtofile(openfile, ft_corextension(argv[1]));
		else if (openfile == 0)
			ft_printf("Error: empty file\n");
		else
			ft_printf("Error: file doesn't exist\n");
		close(openfile);
	}
	else
		ft_printf("Usage: ./asm [file]\n");
	return (0);
}

void	ft_putcharsize_fd(int32_t x, int fd, size_t size)
{
	if (size == 1)
		write(fd, &x, size);
	else if (size == 2)
	{
		x = (((x >> 8) & 0xff) | ((x << 8) & 0xff00));
		write(fd, &x, size);
	}
	else if (size == 4)
	{
		x = ((x >> 24) & 0xff) | ((x << 8) & 0xff0000) |
				((x >> 8) & 0xff00) | ((x << 24) & 0xff000000);
		write(fd, &x, size);
	}
}

char	*ft_corextension(char *str)
{
	int		len;
	char	*newstr;

	len = ft_strlen(str);
	newstr = ft_strnew(len + 1);
	ft_strcpy(newstr, str);
	newstr[len - 1] = 'c';
	newstr[len] = 'o';
	newstr[len + 1] = 'r';
	return (newstr);
}

int		ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}
