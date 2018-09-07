/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarney <mcarney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 18:11:05 by mcarney           #+#    #+#             */
/*   Updated: 2018/09/07 15:19:31 by mcarney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_corewar.h"

void			execute_processes(t_process *pro_lst, t_vm *vm)
{
	while (pro_lst)
	{
		if (pro_lst->op_delay <= 0)
		{
			pro_lst->op = vm->arena[pro_lst->pc];
			if (0 <= pro_lst->op && pro_lst->op < OP_NUMBER)
				pro_lst->op_delay = g_tab[pro_lst->op].cycles;
		}
		if (pro_lst->op_delay > 0)
			pro_lst->op_delay--;
		if (pro_lst->op_delay == 0 && ft_decode(pro_lst, vm->arena))
			g_dispatch[pro_lst->op].fct(vm, pro_lst);
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

t_process		*new_pro(t_process *old, int op, int idx)
{
	int			i;
	t_process	*new;

	if (!(new = (t_process *)malloc(sizeof(t_process))))
		return (NULL);
	new->op = op;
	new->op_delay = 0;
	new->carry = 0;
	new->live = 0;
	ft_memset(&(new->reg), 0, (REG_NUMBER) * sizeof(REG_SIZE));
	if (old)
	{
		new->pc = (idx) ? modify_pc(old->pc + (old->value_p[0] % idx))
						: modify_pc(old->pc + (old->value_p[0]));
		new->carry = old->carry;
		new->owner = old->owner;
		new->live = old->live;
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
