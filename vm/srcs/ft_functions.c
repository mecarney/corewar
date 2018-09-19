/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 15:03:20 by mjacques          #+#    #+#             */
/*   Updated: 2018/09/19 11:31:05 by mcarney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_corewar.h"

#define OP_T(op, i)	g_tab[op].param[i]

void				ft_param(int *param, UCHAR *arena, int pc, int size)
{
	unsigned int	tmp;
	unsigned int	nbr;
	int				len;

	nbr = 0;
	len = size;
	while (--size >= 0)
	{
		ft_memcpy(&tmp, &arena[modify_pc(pc++)], 1);
		nbr = (nbr << 8 & 0xffffff00) | (tmp & 0x000000ff);
	}
	*param = (len == 2) ? (short)nbr : nbr;
}

int					ft_check_param(t_process *p, UCHAR op)
{
	int	i;

	i = -1;
	while (++i < g_tab[op].arg_nbr)
	{
		if (p->type_p[i] == REG_CODE && (OP_T(op, i) != T_REG
			&& OP_T(op, i) != (T_IND | T_REG) && OP_T(op, i) != (T_DIR | T_REG)
			&& OP_T(op, i) != (T_REG | T_DIR | T_IND)))
			return (0);
		else if (p->type_p[i] == DIR_CODE && (OP_T(op, i) != T_DIR
			&& OP_T(op, i) != (T_DIR | T_REG) && OP_T(op, i) != (T_DIR | T_IND)
			&& OP_T(op, i) != (T_REG | T_DIR | T_IND)))
			return (0);
		else if (p->type_p[i] == IND_CODE && (OP_T(op, i) != T_IND
			&& OP_T(op, i) != (T_IND | T_REG) && OP_T(op, i) != (T_DIR | T_IND)
			&& OP_T(op, i) != (T_REG | T_DIR | T_IND)))
			return (0);
	}
	i = -1;
	while (++i < g_tab[op].arg_nbr)
		if (p->type_p[i] == REG_CODE && (REG(i) < 0 || REG(i) >= REG_NUMBER))
			return (0);
	return (1);
}

void				ft_putarena(UINT param, t_vm *vm, int pc, t_process *pro)
{
	int				i;
	int				shift;

	i = -1;
	shift = 32;
	if (pc < 0)
		pc = modify_pc(pc);
	while (++i < REG_SIZE)
	{
		pc = modify_pc(pc);
		vm->arena[pc] = param >> (shift -= 8) & 0xff;
		vm->territory[pc] = pro->owner;
		pc++;
	}
}

int					modify_pc(int pc)
{
	pc = pc % MEM_SIZE;
	if (pc < 0)
		pc = MEM_SIZE + pc;
	return (pc);
}
