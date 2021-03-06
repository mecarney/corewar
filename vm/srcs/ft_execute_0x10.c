/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_0x10.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 15:33:34 by mjacques          #+#    #+#             */
/*   Updated: 2018/09/16 09:03:45 by mcarney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_corewar.h"

void		ft_long_fork(t_vm *vm, t_process *p)
{
	if (ft_check_param(p, p->op))
	{
		pushfront_process(&(vm->pro_lst),
			new_pro(p, vm->arena[modify_pc(p->pc + p->value_p[0])]));
		vm->nbr_of_processes++;
	}
	p->pc = modify_pc(p->pc + p->size_instruction);
}

void		ft_aff(t_vm *vm, t_process *p)
{
	UCHAR	ascii;

	if (ft_check_param(p, p->op))
	{
		ascii = (p->reg[REG(0)] % 256);
		if (vm->v & 1)
			(ft_isascii((int)ascii)) ? mvprintw(65, 195, "%c\n", ascii) : 0;
		else
			(ft_isascii((int)ascii)) ? ft_printf("%c\n", ascii) : 0;
	}
	p->pc = modify_pc(p->pc + p->size_instruction);
}
