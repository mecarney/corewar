/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 18:17:28 by mjacques          #+#    #+#             */
/*   Updated: 2018/09/19 11:25:43 by mcarney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

int		main(int argc, char *argv[])
{
	int		openfile;
	char	*tmp;
	char	*cor_file;

	openfile = 0;
	if (argc == 2)
	{
		if (!(tmp = ft_strrchr(argv[1], '.')) || ft_strcmp(tmp, ".s"))
			ft_error("ERROR: Invalid file extension");
		else if ((openfile = open(argv[1], O_RDONLY)) > 0)
		{
			cor_file = ft_corextension(argv[1]);
			addtofile(openfile, cor_file);
			ft_strdel(&cor_file);
		}
		else if (openfile == 0)
			ft_error("Error: empty file");
		else
			ft_error("Error: file doesn't exist");
		close(openfile);
	}
	else
		ft_printf("Usage: ./asm [file]\n");
	return (0);
}

void	ft_putcharsize_fd(uint32_t x, int fd, size_t size)
{
	if (size == 2)
		x = (((x >> 8) & 0xff) | ((x << 8) & 0xff00));
	else if (size == 4)
	{
		x = ((x >> 24) & 0xff) | ((x << 8) & 0xff0000) |
				((x >> 8) & 0xff00) | ((x << 24) & 0xff000000);
	}
	write(fd, &x, size);
}

char	*ft_corextension(char *str)
{
	int		len;
	char	*newstr;

	len = ft_strlen(str);
	newstr = ft_strnew(len + 2);
	ft_strcpy(newstr, str);
	newstr[len - 1] = 'c';
	newstr[len] = 'o';
	newstr[len + 1] = 'r';
	newstr[len + 2] = 0;
	return (newstr);
}

int		ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}
