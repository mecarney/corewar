/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_0x09.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 15:32:27 by mjacques          #+#    #+#             */
/*   Updated: 2018/09/14 17:06:50 by fhong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_corewar.h"

void	ft_substraction(t_vm *vm, t_process *p)
{
	if (vm && ft_check_param(p, p->op))
	{
		p->reg[REG(2)] = p->reg[REG(0)] - p->reg[REG(1)];
		p->carry = (p->reg[REG(2)]) ? 0 : 1;
	}
	p->pc = modify_pc(p->pc + p->size_instruction);
}

void	ft_and(t_vm *vm, t_process *p)
{
	int i;
	int	value[3];

	i = -1;
	if (ft_check_param(p, p->op))
	{
		while (++i < 2)
		{
			if (p->type_p[i] == REG_CODE)
				value[i] = p->reg[REG(i)];
			else if (p->type_p[i] == DIR_CODE)
				value[i] = p->value_p[i];
			else if (p->type_p[i] == IND_CODE)
				ft_param(&value[i], vm->arena,
					modify_pc(p->pc + (p->value_p[i] % IDX_MOD)), REG_SIZE);
		}
		value[2] = (value[0] & value[1]);
		p->reg[REG(2)] = value[2];
		p->carry = (p->reg[REG(2)]) ? 0 : 1;
	}
	p->pc = modify_pc(p->pc + p->size_instruction);
}

void	ft_or(t_vm *vm, t_process *p)
{
	int i;
	int	value[3];

	i = -1;
	if (ft_check_param(p, p->op))
	{
		while (++i < 2)
		{
			if (p->type_p[i] == REG_CODE)
				value[i] = p->reg[REG(i)];
			else if (p->type_p[i] == DIR_CODE)
				value[i] = p->value_p[i];
			else if (p->type_p[i] == IND_CODE)
				ft_param(&value[i], vm->arena,
					modify_pc(p->pc + (p->value_p[i] % IDX_MOD)), REG_SIZE);
		}
		value[2] = (value[0] | value[1]);
		p->reg[REG(2)] = value[2];
		p->carry = (p->reg[REG(2)]) ? 0 : 1;
	}
	p->pc = modify_pc(p->pc + p->size_instruction);
}

void	ft_xor(t_vm *vm, t_process *p)
{
	int i;
	int	value[3];

	i = -1;
	if (ft_check_param(p, p->op))
	{
		while (++i < 2)
		{
			if (p->type_p[i] == REG_CODE)
				value[i] = p->reg[REG(i)];
			else if (p->type_p[i] == DIR_CODE)
				value[i] = p->value_p[i];
			else if (p->type_p[i] == IND_CODE)
				ft_param(&value[i], vm->arena,
					modify_pc(p->pc + (p->value_p[i] % IDX_MOD)), REG_SIZE);
		}
		value[2] = (value[0] ^ value[1]);
		p->reg[REG(2)] = value[2];
		p->carry = (p->reg[REG(2)]) ? 0 : 1;
	}
	p->pc = modify_pc(p->pc + p->size_instruction);
}

void	ft_zjump(t_vm *vm, t_process *p)
{
	if (vm && ft_check_param(p, p->op) && p->carry == 1)
		p->pc = modify_pc(p->pc + (p->value_p[0] % IDX_MOD));
	else
		p->pc = modify_pc(p->pc + p->size_instruction);
}
