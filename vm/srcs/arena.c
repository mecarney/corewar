/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarney <mcarney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 10:41:59 by mcarney           #+#    #+#             */
/*   Updated: 2018/09/05 21:10:19 by mcarney          ###   ########.fr       */
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

int		ft_champs_return(t_vm *vm)
{
	int i;
	int player;

	i = -1;
	player = 0;
	while (++i < MAX_PLAYERS)
	{
		if (vm->last_live[player] < vm->last_live[i])
			player = i;
	}
	return (player);
}

void		start(t_vm *vm)
{
	UINT	p_alive;
	UINT	i;

	while (vm->pro_lst && ++(vm->vm_cycle) != vm->dump_cycle && vm->ctd > 0)
	{
		// (vm->vm_cycle % 10 == 0) ? ft_printf("%d : %d : %d\n", vm->vm_cycle, vm->ctd, vm->nbr_of_processes) : 0;
		(vm->v & 1) ? decorate_win(vm) : 0;
		vm->new_cycles++;
		p_alive = 0;
		i = -1;
		while (++i < MAX_PLAYERS)
			(vm->players[i].size) ? p_alive += vm->player_alive[i] : 0;
		if (vm->new_cycles % vm->ctd == 0)
		{
			kill_processes(&(vm->pro_lst), &vm->nbr_of_processes);
			i = -1;
			while (++i < MAX_PLAYERS)
				(vm->players[i].size) ? vm->player_alive[i] = 0 : 0;
			(vm->v & 1) ? base(vm) : 0;
		}
		if ((vm->new_cycles % vm->ctd == 0 && p_alive >= NBR_LIVE)
			|| vm->new_cycles / MAX_CHECKS == vm->ctd || vm->ctd < 0)
		{
			vm->ctd -= CYCLE_DELTA;
			vm->new_cycles = 0;
			(vm->v & 1) ? base(vm) : 0;
		}
		(vm->pro_lst) ? execute_processes(vm->pro_lst, vm) : 0;
	}
	(vm->v & 1) ? getch() : 0;
	// ft_printf("final cycle: %d\n", vm->vm_cycle);
	if (vm->vm_cycle == vm->dump_cycle)
	{
		i = -1;
		while (++i < MAX_PLAYERS)
			(vm->players[i].size) ? vm->player_alive[i] = 0 : 0;
		kill_processes(&(vm->pro_lst), &vm->nbr_of_processes);
		print_arena(vm);
	}
	else
	{
		i = ft_champs_return(vm);
		ft_printf("Contestant %d, \"%s\", has won!\n", i + 1, vm->players[i].name);
	}
}
