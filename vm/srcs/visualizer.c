/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarney <mcarney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 06:58:57 by mcarney           #+#    #+#             */
/*   Updated: 2018/09/07 15:26:55 by mcarney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_corewar.h"

void			vm_info(t_vm *vm)
{
	int			i;
	int			y;

	i = -1;
	while (++i < MAX_PLAYERS)
		if (vm->p[i].size)
		{
			y = (i + 2) * 3;
			mvprintw(y, 65 * 3, "Player %d: %s", i + 1, vm->p[i].name);
			mvprintw(y + 1, 65 * 3, "Lives: %d", vm->player_alive[i]);
		}
	mvprintw(57, 70 * 3, "%d", vm->ctd);
	mvprintw(59, 70 * 3, "%d", CYCLE_DELTA);
	mvprintw(61, 70 * 3, "%d", NBR_LIVE);
	mvprintw(63, 70 * 3, "%d", MAX_CHECKS);
}

void			show_territory(t_vm *vm)
{
	int			i;
	int			x;
	int			y;

	x = 0;
	y = 0;
	i = -1;
	while (++i < MEM_SIZE)
	{
		attron(COLOR_PAIR(vm->territory[i]));
		mvprintw(y, x, "%.2x ", vm->arena[i]);
		attroff(COLOR_PAIR(vm->territory[i]));
		x += 3;
		if ((i + 1) % 64 == 0)
		{
			y++;
			x = 0;
		}
	}
}

void			decorate_win(t_vm *vm)
{
	t_process	*tmp;

	show_territory(vm);
	attron(A_STANDOUT);
	tmp = vm->pro_lst;
	while (tmp)
	{
		mvprintw(tmp->pc / 64, tmp->pc % 64 * 3, "%.2x", vm->arena[tmp->pc]);
		tmp = tmp->next;
	}
	attroff(A_STANDOUT);
	mvprintw(0, 70 * 3, "%d", vm->vm_cycle);
	mvprintw(2, 70 * 3, "%d", vm->nbr_of_processes);
	vm_info(vm);
	refresh();
	(vm->vm_cycle > 2700) ? getch() : 0;
}

void			base(t_vm *vm)
{
	clear();
	mvprintw(0, 65 * 3, "Cycle: ");
	mvprintw(2, 65 * 3, "Processes: ");
	mvprintw(57, 65 * 3, "CYCLE_TO_DIE: ");
	mvprintw(59, 65 * 3, "CYCLE_DELTA: ");
	mvprintw(61, 65 * 3, "NBR_LIVE: ");
	mvprintw(63, 65 * 3, "MAX_CHECKS: ");
	decorate_win(vm);
}

void			visualizer(t_vm *vm)
{
	initscr();
	leaveok(stdscr, TRUE);
	noecho();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_GREEN);
	init_pair(2, COLOR_WHITE, COLOR_BLUE);
	init_pair(3, COLOR_WHITE, COLOR_RED);
	init_pair(4, COLOR_WHITE, COLOR_MAGENTA);
	base(vm);
	start(vm);
}
