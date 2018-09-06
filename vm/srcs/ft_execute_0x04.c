/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_0x04.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 17:07:42 by mjacques          #+#    #+#             */
/*   Updated: 2018/09/05 21:07:42 by mcarney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_corewar.h"

void	ft_null(t_vm *vm, t_process *p)
{
	(void)vm;
	p->pc = (p->pc + 1) % MEM_SIZE;
	// p->op_delay = g_tab[vm->arena[p->pc]].cycles;
}

void	ft_live(t_vm *vm, t_process *p)
{
	int live;

	live = -(p->value_p[0]);
	if (ft_check_param(p, vm->arena[p->pc]))
	{
		(live > 0 && live <= MAX_PLAYERS) ? vm->player_alive[live - 1] += 1: 0;
		(live > 0 && live <= MAX_PLAYERS) ? vm->last_live[live - 1] = vm->vm_cycle : 0;
		p->live = 1;
	}
	p->pc = modify_pc(p->pc + p->size_instruction);
	// p->op_delay = g_tab[vm->arena[p->pc]].cycles;
}

void	ft_load(t_vm *vm, t_process *p)
{
	int	value;

	value = -3;
	if (ft_check_param(p, vm->arena[p->pc]))
	{
		if (p->type_p[0] == IND_CODE)
			ft_param(&value, vm->arena,
				modify_pc(p->pc + (p->value_p[0] % IDX_MOD)), REG_SIZE);
		else
			value = p->value_p[0];
		p->reg[REG(1)] = value;
		p->carry = (value) ? 0 : 1;
	}
	p->pc = modify_pc(p->pc + p->size_instruction);
	// p->op_delay = g_tab[vm->arena[p->pc]].cycles;
	// ft_printf("%d %d %x\n", vm->vm_cycle, modify_pc(p->pc + (p->value_p[0] % IDX_MOD)), value);
}

void	ft_store(t_vm *vm, t_process *p)
{
	int value;
	int reg;

	reg = p->value_p[0] - 1;
	if (ft_check_param(p, vm->arena[p->pc]))
	{
		value = p->reg[reg];
		if (p->type_p[1] == REG_CODE)
			p->reg[p->value_p[1] - 1] = value;
		else
			ft_putarena(value, vm,
				modify_pc(p->pc + (p->value_p[1] % IDX_MOD)), p);
	}
	p->pc = modify_pc(p->pc + p->size_instruction);
	// p->op_delay = g_tab[vm->arena[p->pc]].cycles;
}

void	ft_addition(t_vm *vm, t_process *p)
{
	if (ft_check_param(p, vm->arena[p->pc]))
	{
		p->reg[REG(2)] = p->reg[REG(0)] + p->reg[REG(1)];
		p->carry = (p->reg[REG(2)]) ? 0 : 1;
	}
	p->pc = modify_pc(p->pc + p->size_instruction);
	// p->op_delay = g_tab[vm->arena[p->pc]].cycles;
}
