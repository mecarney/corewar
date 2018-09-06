/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_0x09.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 15:32:27 by mjacques          #+#    #+#             */
/*   Updated: 2018/09/05 14:26:33 by mcarney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_corewar.h"

void	ft_substraction(t_vm *vm, t_process *p)
{
	if (ft_check_param(p, vm->arena[p->pc]))
	{
		p->reg[REG(2)] = p->reg[REG(0)] - p->reg[REG(1)];
		// p->reg[REG(2)] = p->reg[REG(1)] - p->reg[REG(0)];
		p->carry = (p->reg[REG(2)]) ? 0 : 1;
	}
	p->pc = modify_pc(p->pc + p->size_instruction);
	// p->op_delay = g_tab[vm->arena[p->pc]].cycles;
}

void	ft_and(t_vm *vm, t_process *p)
{
	int i;
	int	value[3];

	i = -1;
	if (ft_check_param(p, vm->arena[p->pc]))
	{
		while (++i < 2)
		{
			if (p->type_p[i] == REG_CODE)
				value[i] = p->reg[REG(i)];
			else if (p->type_p[i] == DIR_CODE)
				value[i] = p->value_p[i];
			else if (p->type_p[i] == IND_CODE)
				ft_param(&value[i], vm->arena,
					modify_pc(p->pc + (p->value_p[i] % IDX_MOD)), IND_SIZE);
		}
		value[2] = (value[0] & value[1]);
		p->reg[REG(2)] = value[2];
		p->carry = (p->reg[REG(2)]) ? 0 : 1;
	}
	p->pc = modify_pc(p->pc + p->size_instruction);
	// p->op_delay = g_tab[vm->arena[p->pc]].cycles;
}

void	ft_or(t_vm *vm, t_process *p)
{
	int i;
	int	value[3];

	i = -1;
	if (ft_check_param(p, vm->arena[p->pc]))
	{
		while (++i < 2)
		{
			if (p->type_p[i] == REG_CODE)
				value[i] = p->reg[REG(i)];
			else if (p->type_p[i] == DIR_CODE)
				value[i] = p->value_p[i];
			else if (p->type_p[i] == IND_CODE)
				ft_param(&value[i], vm->arena,
					modify_pc(p->pc + (p->value_p[i] % IDX_MOD)), IND_SIZE);
		}
		value[2] = (value[0] | value[1]);
		p->reg[REG(2)] = value[2];
		p->carry = (p->reg[REG(2)]) ? 0 : 1;
	}
	p->pc = modify_pc(p->pc + p->size_instruction);
	// p->op_delay = g_tab[vm->arena[p->pc]].cycles;
}

void	ft_xor(t_vm *vm, t_process *p)
{
	int i;
	int	value[3];

	i = -1;
	if (ft_check_param(p, vm->arena[p->pc]))
	{
		while (++i < 2)
		{
			if (p->type_p[i] == REG_CODE)
				value[i] = p->reg[REG(i)];
			else if (p->type_p[i] == DIR_CODE)
				value[i] = p->value_p[i];
			else if (p->type_p[i] == IND_CODE)
				ft_param(&value[i], vm->arena,
					modify_pc(p->pc + (p->value_p[i] % IDX_MOD)), IND_SIZE);
		}
		value[2] = (value[0] ^ value[1]);
		p->reg[REG(2)] = value[2];
		p->carry = (p->reg[REG(2)]) ? 0 : 1;
	}
	p->pc = modify_pc(p->pc + p->size_instruction);
	// p->op_delay = g_tab[vm->arena[p->pc]].cycles;
}

void	ft_zjump(t_vm *vm, t_process *p)
{
	// ft_printf("JUMP value_p = %d, carry = %d, \n", p->value_p[0], p->carry);
	if (ft_check_param(p, vm->arena[p->pc]) && p->carry == 1)
		p->pc = modify_pc(p->pc + (p->value_p[0] % IDX_MOD));
	else
		p->pc = modify_pc(p->pc + p->size_instruction);
	// ft_printf("next pc = %d\n", p->pc);
	// p->op_delay = g_tab[vm->arena[p->pc]].cycles;
}
