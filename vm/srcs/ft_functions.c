/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 15:03:20 by mjacques          #+#    #+#             */
/*   Updated: 2018/09/04 21:30:37 by fhong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_corewar.h"

#define OP_T(op, i)	g_tab[op].param[i]

void	ft_param(int *param, UCHAR *arena, int pc, int size)
{
	int tmp;
	int nbr;
	int len;

	nbr = 0;
	len = size;
	while (--size >= 0)
	{
		ft_memcpy(&tmp, &arena[(pc++) % MEM_SIZE], 1);
		nbr = (nbr << 8 & 0xffffff00) | (tmp & 0x000000ff);
	}
	*param = (len == 2) ? (short)nbr : nbr;
}

int		ft_check_param(t_process *p, UCHAR op)
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

// void	ft_putarena(UINT param, t_vm *vm, int pc, t_process *pro)
// {
// 	int sft;
// 	int size;
//
// 	size = REG_SIZE;
// 	sft = size - 1;
// 	while (--size >= 0)
// 	{
// 		// vm->arena[(pc + size) % MEM_SIZE] = (param >> 8 * (-size + sft) & 0xff);
// 		// ft_printf("%x\n", (param >> 8 * (-size + sft) & 0xff));
// 		vm->territory[(pc + size) % MEM_SIZE] = (param >> 8 * (-size + sft) & 0xff);
// 	}
// 	(void)pro;
// }

void	ft_putarena(UINT param, t_vm *vm, int pc, t_process *pro)
{
	int i;
	int	shift;
	unsigned int tmp;

	i = -1;
	shift = 32;
	if (pc < 0)
		pc = MEM_SIZE - pc;
	while (++i < REG_SIZE)
	{
			// ft_printf("param: %p, vm->pro: %p cycle: %d\n", &param, vm->pro_lst, vm->vm_cycle);
		pc = (pc % MEM_SIZE);
		tmp = param >> (shift -= 8) & 0xff;
		// ft_printf("tmp: %d, pc: %d\n", tmp, pc);
		vm->arena[pc] = tmp;
		vm->territory[pc] = pro->owner;
		pc += 1;
	}
	(void)pro;
}

int		ft_return_error(char const *str)
{
	ft_putendl(str);
	exit(EXIT_FAILURE);
}

int		modify_pc(int pc)
{
	if (pc < 0)
		pc = MEM_SIZE + pc;
	pc = pc % MEM_SIZE;
	return (pc);
}
