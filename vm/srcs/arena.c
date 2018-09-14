/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarney <mcarney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 10:41:59 by mcarney           #+#    #+#             */
/*   Updated: 2018/09/14 15:41:55 by mcarney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_corewar.h"

void		print_arena(t_vm *vm)
{
	int		i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		(i % 64 == 0 && i != (MEM_SIZE - 1)) ? ft_printf("0x%04x : ", i) : 0;
		ft_printf("%.2x ", vm->arena[i]);
		((i + 1) % 64 == 0) ? ft_printf("\n") : 0;
	}
}

int			ft_champs_return(t_vm *vm)
{
	int		i;
	int		player;

	i = -1;
	while (++i < MAX_PLAYERS)
		(vm->p[i].size) ? player = i : 0;
	i = -1;
	while (++i < MAX_PLAYERS)
	{
		if (vm->p[i].size && vm->last_live[i] > vm->last_live[player])
			player = i;
	}
	return (player);
}

void		loop(t_vm *vm, int i)
{
	UINT	p_alive;

	(vm->v & 1) ? decorate_win(vm) : 0;
	p_alive = 0;
	while (++i < MAX_PLAYERS)
		(vm->p[i].size) ? p_alive += vm->player_alive[i] : 0;
	if (++vm->new_cycles % vm->ctd == 0 || TIME_TO_DIE)
	{
		if (vm->new_cycles % vm->ctd == 0)
		{
			kill_processes(&(vm->pro_lst), &vm->nbr_of_processes);
			i = -1;
			while (++i < MAX_PLAYERS)
				(vm->p[i].size) ? vm->player_alive[i] = 0 : 0;
		}
		if (vm->nbr_lives >= NBR_LIVE || TIME_TO_DIE)
		{
			vm->ctd -= CYCLE_DELTA;
			vm->ttd_cycles = 0;
		}
		vm->nbr_lives = 0;
		vm->new_cycles = 0;
		(vm->v & 1) ? base(vm) : 0;
	}
	(vm->pro_lst) ? execute_processes(vm->pro_lst, vm) : 0;
}

void		start(t_vm *vm)
{
	int		i;

	while (vm->pro_lst && ++(vm->vm_cycle) != vm->dump_cycle && vm->ctd > 0)
	{
		loop(vm, -1);
		vm->ttd_cycles++;
	}
	(vm->v & 1) ? decorate_win(vm) : 0;
	(vm->v & 1) ? getch() : 0;
	if (vm->vm_cycle == vm->dump_cycle)
	{
		(vm->v & 1) ? endwin() : 0;
		i = -1;
		while (++i < MAX_PLAYERS)
			(vm->p[i].size) ? vm->player_alive[i] = 0 : 0;
		kill_processes(&(vm->pro_lst), &vm->nbr_of_processes);
		print_arena(vm);
	}
	else
	{
		(vm->v & 1) ? endwin() : 0;
		i = ft_champs_return(vm);
		ft_printf("Contestant %d, \"%s\", has won !\n", i + 1, vm->p[i].name);
	}
}
