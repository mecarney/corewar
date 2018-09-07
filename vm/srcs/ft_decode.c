/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhong <fhong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 00:22:43 by fhong             #+#    #+#             */
/*   Updated: 2018/09/07 14:56:50 by mcarney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_corewar.h"

int		ft_instruction_edge(t_process *p, UCHAR op)
{
	p->type_p[0] = DIR_CODE;
	p->size_p[0] = (op == 1) ? DIR_SIZE : DIR_SIZE / 2;
	p->size_instruction = ((op == 1) ? 5 : 3);
	return (1);
}

int		ft_instruction(t_process *p, UCHAR op, UCHAR op_type)
{
	int i;
	int mercy;
	int byte;
	int shift;

	if (op == 1 || op == 9 || op == 12 || op == 15)
		return (ft_instruction_edge(p, op));
	i = -1;
	shift = 8;
	mercy = 1;
	while (++i < g_tab[op].arg_nbr && op != 0)
	{
		p->type_p[i] = (op_type >> (shift -= 2) & 3);
		if (p->type_p[i] == REG_CODE)
			p->size_p[i] = 1;
		else if (p->type_p[i] == DIR_CODE)
			p->size_p[i] = (g_tab[op].truncation == 0) ? 4 : 2;
		else if (p->type_p[i] == IND_CODE)
			p->size_p[i] = 2;
		else
			mercy = 0;
	}
	byte = g_tab[op].is_coding_byte;
	p->size_instruction = 1 + byte + p->size_p[0] + p->size_p[1] + p->size_p[2];
	return (mercy);
}

void	ft_add_param(t_process *p, UCHAR *arena, int op_code)
{
	int i;
	int shift;
	int byte;

	byte = g_tab[op_code].is_coding_byte;
	i = -1;
	shift = 0;
	while (++i < g_tab[op_code].arg_nbr && op_code != 0)
	{
		ft_param(&p->value_p[i], arena,
			(p->pc + 1 + byte + shift), p->size_p[i]);
		shift += p->size_p[i];
	}
}

void	ft_init_player(t_process *p)
{
	ft_bzero(p->value_p, 3 * 4);
	ft_bzero(p->type_p, 3);
	ft_bzero(p->size_p, 3);
	p->size_instruction = 0;
}

int		ft_decode(t_process *p, UCHAR *arena)
{
	ft_init_player(p);
	if (!(0 <= p->op && p->op < OP_NUMBER))
	{
		p->pc = modify_pc(p->pc + 1);
		p->op_delay = 0;
		return (0);
	}
	if (!ft_instruction(p, p->op, arena[(p->pc + 1) % MEM_SIZE]))
	{
		p->pc = modify_pc(p->pc + p->size_instruction);
		p->op_delay = 0;
		return (0);
	}
	ft_add_param(p, arena, p->op);
	return (1);
}
