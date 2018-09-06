/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_op_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhong <fhong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 23:57:39 by fhong             #+#    #+#             */
/*   Updated: 2018/08/29 03:46:09 by mjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_asm.h"

int		find_label_index(t_label *list, char *str)
{
	int		len;
	char	*str_label;

	len = 0;
	while (str[len] && str[len] != SEPARATOR_CHAR && !ft_isspace(str[len]))
		len++;
	if (str[len - 1] == SEPARATOR_CHAR)
		len--;
	str_label = ft_strsub(str, 0, len);
	while (list)
	{
		if (list->label && ft_strcmp(str_label, list->label) == 0)
			return (list->index);
		list = list->next;
	}
	return (-1);
}

void	print_arg_type(int *arg_type, int file)
{
	int nbr;

	nbr = 0;
	nbr += (arg_type[0] / 10 * 128) + (arg_type[0] % 10 * 64);
	nbr += (arg_type[1] / 10 * 32) + (arg_type[1] % 10 * 16);
	nbr += (arg_type[2] / 10 * 8) + (arg_type[2] % 10 * 4);
	ft_putcharsize_fd(nbr, file, 1);
}

char	*print_reg(char *line, int size, int file)
{
	int nbr;

	nbr = 0;
	line = ft_strchr(line, 'r') + 1;
	if (*line == '-' || *line == '+' || ft_isdigit(*line))
		nbr = ft_atoi(line);
	else
		ft_error("ERROR: Invalid number");
	if (nbr > REG_NUMBER)
		ft_error("ERROR: Register number too big");
	ft_putcharsize_fd(nbr, file, size);
	return (line);
}

char	*print_dir(t_line *tline, t_label *label, int file, int index)
{
	int		nbr;
	int		dir_size;
	char	*line;

	nbr = 0;
	line = tline->str;
	dir_size = (tline->op->truncation == 1) ? DIR_SIZE / 2 : DIR_SIZE;
	line = ft_strchr(line, DIRECT_CHAR) + 1;
	if (*line == LABEL_CHAR)
		nbr = find_label_index(label, line + 1) - index;
	else if (*line == '-' || *line == '+' || ft_isdigit(*line))
		nbr = ft_atoi(line);
	else
		ft_error("ERROR: Invalid number");
	ft_putcharsize_fd(nbr, file, dir_size);
	return (line);
}

char	*print_ind(t_line *tline, t_label *label, int file, int index)
{
	int		nbr;
	char	*tmp;
	char	*line;

	nbr = 0;
	line = tline->str;
	if ((tmp = ft_strchr(line, LABEL_CHAR)) != NULL)
		nbr = find_label_index(label, tmp + 1) - index;
	else if (*line == '-' || *line == '+' || ft_isdigit(*line))
		nbr = ft_atoi(line);
	else
		ft_error("ERROR: Invalid number");
	ft_putcharsize_fd(nbr, file, IND_SIZE);
	return (line);
}
