/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarney <mcarney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 18:11:05 by mcarney           #+#    #+#             */
/*   Updated: 2018/09/05 20:09:34 by mcarney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_corewar.h"

void			execute_processes(t_process *pro_lst, t_vm *vm)
{
	int i;

	while (pro_lst)
	{
		// (vm->vm_cycle < 15 && pro_lst->owner == 2) ? ft_printf("????%d %x %d\n", vm->vm_cycle, vm->arena[pro_lst->pc], pro_lst->op_delay) : 0;
		(pro_lst->op_delay > 0) ? pro_lst->op_delay -= 1 : 0;
		(pro_lst->pc < 0) ? pro_lst->pc = MEM_SIZE - pro_lst->pc : 0;
		// (vm->vm_cycle < 500 && vm->vm_cycle > 400 && pro_lst->owner == 2) ? ft_printf("%d %x\n", pro_lst->op_delay, vm->arena[pro_lst->pc]) : 0;
		// if (vm->arena[pro_lst->pc] > OP_NUMBER)
		// {
		// 	pro_lst->op_delay = g_tab[vm->arena[++pro_lst->pc]].cycles;
		// 	ft_printf("%d : %d\n", vm->arena[++pro_lst->pc], pro_lst->op_delay);
		// }
		if (pro_lst->op_delay == 0 && ft_decode(pro_lst, vm->arena))
		{
			i = -1;
			while (++i < OP_NUMBER)
			{
				if (g_dispatch[i].op_code == vm->arena[pro_lst->pc])
				{
					// ft_printf("owner: %d, OP: %x, PC: %d, cycle: %d\t",
						// pro_lst->owner, vm->arena[pro_lst->pc], pro_lst->pc, vm->vm_cycle);
					// ft_printf("v: |%d|%d|%d|\n", pro_lst->value_p[0], pro_lst->value_p[1], pro_lst->value_p[2]);
					// for (int j = 0; j < 16; j++)
					// {
					// 	vm->players[pro_lst->owner - 1].reg[j] = 0;
					// 	ft_printf("|%u", pro_lst->reg[j]);
					// }
					// ft_printf("|\n");
					g_dispatch[i].fct(vm, pro_lst);
					break ;
				}
			}
		}
		if (pro_lst->op_delay <= 0)
		{
			if (0 <= vm->arena[pro_lst->pc] && vm->arena[pro_lst->pc] < OP_NUMBER)
				pro_lst->op_delay = g_tab[vm->arena[pro_lst->pc]].cycles;
				// (vm->vm_cycle < 15 && pro_lst->owner == 2) ? ft_printf("%d %x %d\n", vm->vm_cycle, vm->arena[pro_lst->pc], pro_lst->op_delay) : 0;
			else
			{
				// pro_lst->pc = modify_pc(pro_lst->pc + 1);
				if (0 <= vm->arena[pro_lst->pc] && vm->arena[pro_lst->pc] < OP_NUMBER)
					pro_lst->op_delay = g_tab[vm->arena[pro_lst->pc]].cycles;
			}
			// (vm->vm_cycle < 15) ? ft_printf("%d %x %d\n", vm->vm_cycle, vm->arena[pro_lst->pc], pro_lst->op_delay) : 0;
		}
		// if (pro_lst->pc >= 0 && pro_lst->pc <= OP_NUMBER)
		// 	pro_lst->op_delay = g_tab[pro_lst->pc].cycles;
		pro_lst = pro_lst->next;
	}
}

void			kill_processes(t_process **pro_lst, UINT *nbrpro)
{
	t_process	*to_traverse;
	t_process	*tmp;
	t_process	*prev;

	to_traverse = *pro_lst;
	prev = NULL;
	while (to_traverse)
	{
		tmp = to_traverse->next;
		if (!(to_traverse->live))
		{
			if (prev)
				prev->next = tmp;
			else
				*pro_lst = tmp;
			free(to_traverse);
			*nbrpro -= 1;
		}
		else
		{
			to_traverse->live = 0;
			prev = to_traverse;
		}
		to_traverse = tmp;
	}
}

void			free_processes(t_process **pro_lst)
{
	t_process	*to_traverse;
	t_process	*tmp;

	to_traverse = *pro_lst;
	while (to_traverse)
	{
		tmp = to_traverse->next;
		free(to_traverse);
		to_traverse = tmp;
	}
	*pro_lst = NULL;
}

t_process		*new_process(t_process *old, int op, int idx)
{
	int				i;
	t_process	*new;

	if (!(new = (t_process *)malloc(sizeof(t_process))))
		return (NULL);
	new->next_op = -1;
	new->op_delay = 0;
	new->carry = 0;
	new->nbr = 0;
	new->live = 0;
	ft_init_player(new);
	ft_memset(&(new->reg), 0, (REG_NUMBER) * sizeof(REG_SIZE));
	if (old)
	{
		new->op_delay = g_tab[op].cycles;
		new->pc = (idx) ? modify_pc(old->pc + (old->value_p[0] % idx)) : modify_pc(old->pc + (old->value_p[0]));
		new->carry = old->carry;
		new->owner = old->owner;
		new->nbr = old->nbr + 1;
		i = -1;
		while (++i < 16)
			new->reg[i] = old->reg[i];
	}
	return (new);
}

void			pushfront_process(t_process **alst, t_process *new)
{
	new->next = *alst;
	*alst = new;
}
