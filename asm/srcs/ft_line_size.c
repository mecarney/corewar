/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhong <fhong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 15:30:56 by fhong             #+#    #+#             */
/*   Updated: 2018/09/19 12:54:48 by mjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

t_op	g_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

int		arg_type(char **line, int i, int j)
{
	char c;

	if (**line == 'r' || **line == DIRECT_CHAR || ft_isdigit(**line)
		|| **line == '-' || **line == '+' || **line == LABEL_CHAR)
	{
		c = **line;
		while (**line && **line != SEPARATOR_CHAR && **line != COMMENT_CHAR)
			(*line)++;
		if (**line && **line == SEPARATOR_CHAR)
			(*line)++;
		if (c == 'r' && (g_tab[i].p[j] == T_REG || g_tab[i].p[j] == (T_IND
			| T_REG) || g_tab[i].p[j] == (T_DIR | T_REG)
			|| g_tab[i].p[j] == (T_REG | T_DIR | T_IND)))
			return (REG_CODE);
		else if (c == DIRECT_CHAR && (g_tab[i].p[j] == T_DIR
			|| g_tab[i].p[j] == (T_DIR | T_REG) || g_tab[i].p[j] == (T_DIR
			| T_IND) || g_tab[i].p[j] == (T_REG | T_DIR | T_IND)))
			return (DIR_CODE);
		else if (g_tab[i].p[j] == T_IND || g_tab[i].p[j] == (T_IND | T_REG)
			|| g_tab[i].p[j] == (T_DIR | T_IND)
			|| g_tab[i].p[j] == (T_REG | T_DIR | T_IND))
			return (IND_CODE);
	}
	ft_error("ERROR: Invalid parameter");
	return (0);
}

int		find_op(char **line)
{
	char	*op_name;
	int		op_name_len;
	int		i;

	i = -1;
	op_name_len = 0;
	while (**line && ft_isspace(**line))
		(*line)++;
	while ((*line)[op_name_len] && !ft_isspace((*line)[op_name_len]))
		op_name_len++;
	op_name = ft_strsub(*line, 0, op_name_len);
	while (++i < 16)
	{
		if (ft_strstr(g_tab[i].op_name, op_name) != NULL)
		{
			check_parameter(i, line);
			while (!ft_isspace(**line))
				(*line)++;
			ft_strdel(&op_name);
			return (i);
		}
	}
	ft_strdel(&op_name);
	ft_error("ERROR: op_code invalid");
	return (-1);
}

int		total_arg_index(t_op *op, int j)
{
	int index;

	index = 0;
	while (j > 0)
	{
		j--;
		if (op->truncation && op->p[j] == DIR_CODE)
			index += (DIR_SIZE / 2);
		else if (!op->truncation && op->p[j] == DIR_CODE)
			index += DIR_SIZE;
		else if (op->p[j] == REG_CODE)
			index += 1;
		else if (op->p[j] == IND_CODE)
			index += IND_SIZE;
	}
	return (index);
}

void	copy_g_op(t_op *op, t_op tab)
{
	op->op_name = ft_strdup(tab.op_name);
	op->arg_nbr = tab.arg_nbr;
	op->p[0] = tab.p[0];
	op->p[1] = tab.p[1];
	op->p[2] = tab.p[2];
	op->opcode = tab.opcode;
	op->cycle_req = tab.cycle_req;
	op->comment = ft_strdup(tab.comment);
	op->is_coding_byte = tab.is_coding_byte;
	op->truncation = tab.truncation;
}

int		get_index(char *line, t_op *op)
{
	int		arg_code;
	int		i;
	int		j;
	int		index;

	if (!line)
		return (0);
	index = 1;
	i = find_op(&line);
	copy_g_op(op, g_tab[i]);
	j = 0;
	while (*line)
	{
		while (*line && ft_isspace(*line))
			(line)++;
		if (!*line || *line == '#' || ((arg_code = arg_type(&line, i, j)) == 0))
			break ;
		op->p[j] = arg_code;
		j++;
	}
	ft_checkline(&line);
	index += total_arg_index(op, j);
	return ((g_tab[i].is_coding_byte == 1) ? index + 1 : index);
}
