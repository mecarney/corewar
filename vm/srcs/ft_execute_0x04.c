/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_0x04.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 17:07:42 by mjacques          #+#    #+#             */
/*   Updated: 2018/09/14 17:06:46 by fhong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_corewar.h"

void	ft_null(t_vm *vm, t_process *p)
{
	(vm) ? p->pc = (p->pc + 1) % MEM_SIZE : 0;
}

void	ft_live(t_vm *vm, t_process *p)
{
	int live;

	live = -(p->value_p[0]);
	p->live = 1;
	vm->nbr_lives++;
	if (ft_check_param(p, p->op) && live > 0 && live <= MAX_PLAYERS)
	{
		vm->last_live[live - 1] = vm->vm_cycle;
		vm->player_alive[live - 1]++;
	}
	p->pc = modify_pc(p->pc + p->size_instruction);
}

void	ft_load(t_vm *vm, t_process *p)
{
	int	value;

	if (ft_check_param(p, p->op))
	{
		if (p->type_p[0] == IND_CODE)
			ft_param(&value, vm->arena,
				modify_pc(p->pc + (p->value_p[0] % IDX_MOD)), REG_SIZE);
		else
			value = p->value_p[0];
		p->reg[REG(1)] = value;
		p->carry = (p->reg[REG(1)]) ? 0 : 1;
	}
	p->pc = modify_pc(p->pc + p->size_instruction);
}

void	ft_store(t_vm *vm, t_process *p)
{
	int value;

	if (ft_check_param(p, p->op))
	{
		value = p->reg[REG(0)];
		if (p->type_p[1] == REG_CODE)
			p->reg[REG(1)] = value;
		else
			ft_putarena(value, vm,
				modify_pc(p->pc + (p->value_p[1] % IDX_MOD)), p);
	}
	p->pc = modify_pc(p->pc + p->size_instruction);
}

void	ft_addition(t_vm *vm, t_process *p)
{
	(void)vm;
	if (ft_check_param(p, p->op))
	{
		p->reg[REG(2)] = p->reg[REG(0)] + p->reg[REG(1)];
		p->carry = (p->reg[REG(2)]) ? 0 : 1;
	}
	p->pc = modify_pc(p->pc + p->size_instruction);
}
