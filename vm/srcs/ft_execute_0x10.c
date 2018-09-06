/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_0x10.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 15:33:34 by mjacques          #+#    #+#             */
/*   Updated: 2018/09/05 20:09:14 by mcarney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_corewar.h"

void	ft_long_fork(t_vm *vm, t_process *p)
{
	if (ft_check_param(p, vm->arena[p->pc]))
	{
		pushfront_process(&(vm->pro_lst),
			new_process(p, vm->arena[modify_pc(p->pc + p->value_p[0])], 0));
		vm->nbr_of_processes++;
	}
	p->pc = modify_pc(p->pc + p->size_instruction);
	// p->op_delay = g_tab[vm->arena[p->pc]].cycles;
}

void	ft_aff(t_vm *vm, t_process *p)
{
	// UCHAR ascii;

	if (ft_check_param(p, vm->arena[p->pc]))
	{
		// ascii = (p->reg[REG(0)] % 256);
		// 	ft_printf("ascii = %d\n", ascii);
		// (ft_isascii((int)ascii)) ? ft_printf("%c\n", ascii) : 0;
	}
	p->pc = modify_pc(p->pc + p->size_instruction);
	// p->op_delay = g_tab[vm->arena[p->pc]].cycles;
}
