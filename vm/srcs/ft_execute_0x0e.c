/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_0x0e.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 15:33:07 by mjacques          #+#    #+#             */
/*   Updated: 2018/09/13 10:45:49 by mcarney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_corewar.h"

void	ft_load_index(t_vm *vm, t_process *p)
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
					modify_pc(p->pc + p->value_p[i] % IDX_MOD), REG_SIZE);
		}
		value[2] = value[0] + value[1];
		ft_param(&p->reg[REG(2)], vm->arena,
			modify_pc(p->pc + (value[2] % IDX_MOD)), REG_SIZE);
	}
	p->pc = modify_pc(p->pc + p->size_instruction);
}

void	ft_store_index(t_vm *vm, t_process *p)
{
	int	i;
	int	value[3];

	i = 0;
	if (ft_check_param(p, p->op))
	{
		while (++i < 3)
		{
			if (p->type_p[i] == REG_CODE)
				value[i] = p->reg[REG(i)];
			else if (p->type_p[i] == DIR_CODE)
				value[i] = p->value_p[i];
			else if (p->type_p[i] == IND_CODE)
				ft_param(&value[i], vm->arena,
					modify_pc(p->pc + (p->value_p[1] % IDX_MOD)), REG_SIZE);
		}
		value[0] = value[1] + value[2];
		ft_putarena(p->reg[REG(0)], vm,
				modify_pc((p->pc) + value[0] % IDX_MOD), p);
	}
	p->pc = modify_pc(p->pc + p->size_instruction);
}

void	ft_fork(t_vm *vm, t_process *p)
{
	if (ft_check_param(p, p->op))
	{
		pushfront_process(&(vm->pro_lst),
			new_pro(p, vm->arena[modify_pc(p->pc + p->value_p[0])], IDX_MOD));
		vm->nbr_of_processes++;
	}
	p->pc = modify_pc(p->pc + p->size_instruction);
}

void	ft_long_load(t_vm *vm, t_process *p)
{
	int	value;

	if (ft_check_param(p, p->op))
	{
		if (p->type_p[0] == IND_CODE)
			ft_param(&value, vm->arena,
				modify_pc(p->pc + p->value_p[0]), REG_SIZE);
		else
			value = p->value_p[0];
		p->reg[REG(1)] = value;
		p->carry = (p->reg[REG(1)]) ? 0 : 1;
	}
	p->pc = modify_pc(p->pc + p->size_instruction);
}

void	ft_long_load_index(t_vm *vm, t_process *p)
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
					modify_pc(p->pc + p->value_p[i]), IND_SIZE);
		}
		value[2] = value[0] + value[1];
		ft_param(&p->reg[REG(2)], vm->arena,
			modify_pc(p->pc + value[2]), REG_SIZE);
		p->carry = (p->reg[REG(2)]) ? 0 : 1;
	}
	p->pc = modify_pc(p->pc + p->size_instruction);
}
