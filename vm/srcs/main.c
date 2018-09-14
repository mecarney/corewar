/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarney <mcarney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 10:41:25 by mcarney           #+#    #+#             */
/*   Updated: 2018/09/14 15:54:07 by mcarney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_corewar.h"

t_op_dispatch		g_dispatch[OP_NUMBER] =
{
	{0x00, &ft_null},
	{0x01, &ft_live},
	{0x02, &ft_load},
	{0x03, &ft_store},
	{0x04, &ft_addition},
	{0x05, &ft_substraction},
	{0x06, &ft_and},
	{0x07, &ft_or},
	{0x08, &ft_xor},
	{0x09, &ft_zjump},
	{0x0a, &ft_load_index},
	{0x0b, &ft_store_index},
	{0x0c, &ft_fork},
	{0x0d, &ft_long_load},
	{0x0e, &ft_long_load_index},
	{0x0f, &ft_long_fork},
	{0x10, &ft_aff}
};

t_op	g_tab[OP_NUMBER] =
{
	{0, 0, {0}, 0, 0, 0, 0, 0},
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0}
};

/*
** If there's a -dump, check the next argument for a number greater than zero.
** Store number so we can print and exit if that cycle is reached.
*/

void				dump_flag(int ac, char **av, t_vm *vm, int *i)
{
	if (*i + 1 < ac && ft_atoi(av[*i + 1]))
	{
		vm->dump_cycle = ft_atoi(av[*i + 1]);
		*i += 1;
	}
	else
		ft_return_error("Error: invalid dump parameter");
}

/*
** If there's a -n, check for a number and cor file as the next two arguments.
** Add a new player with the custom number and read the correct next argument.
*/

void				n_flag(int ac, char **av, t_vm *vm, int *i)
{
	char			*s;

	if (!(ft_atoi(av[*i + 1]) <= MAX_PLAYERS && ft_atoi(av[*i + 1]) != 0))
		ft_return_error("Error: invalid player number");
	else if (*i + 1 < ac && '0' < av[*i + 1][0]
		&& *i + 2 < ac && (s = ft_strstr(av[*i + 2], ".cor"))
		&& s != av[*i + 2] && !s[4])
	{
		new_pn(av, *i, vm);
		*i += 2;
	}
	else
		ft_return_error("Error: invalid parameters");
}

/*
** Check for -dump, check for -n player number flag, and check for cor file.
*/

void				parse_av(int ac, char **av, t_vm *vm)
{
	int				i;
	char			*s;

	i = 0;
	while (av[++i])
	{
		if (!ft_strcmp("-v", av[i]))
			vm->v |= 1;
		else if (!ft_strcmp("-dump", av[i]))
			dump_flag(ac, av, vm, &i);
		else if (!ft_strcmp("-n", av[i]))
			n_flag(ac, av, vm, &i);
		else if (!((s = ft_strstr(av[i], ".cor")) && s != av[i] && !s[4]))
			ft_return_error("Error: invalid parameters");
	}
	i = 0;
	while (av[++i])
	{
		if (!ft_strcmp("-n", av[i]))
			i += 2;
		else if ((s = ft_strstr(av[i], ".cor")) && s != av[i] && !s[4])
			new_p(av, i, vm);
	}
}

/*
** Set defaults for vm.
*/

void				defaults(t_vm *vm)
{
	int				i;

	vm->pro_lst = NULL;
	vm->nbrp = 0;
	vm->ctd = CYCLE_TO_DIE;
	vm->vm_cycle = 0;
	vm->new_cycles = 0;
	vm->ttd_cycles = 0;
	vm->dump_cycle = -1;
	vm->v &= 0;
	vm->nbr_of_processes = 0;
	vm->nbr_lives = 0;
	i = -1;
	while (++i < MAX_PLAYERS)
	{
		vm->player_alive[i] = 0;
		vm->p[i].size = 0;
	}
	ft_bzero(vm->last_live, MAX_PLAYERS * 4);
	ft_bzero(vm->arena, MEM_SIZE);
	ft_bzero(vm->territory, MEM_SIZE);
}

int					main(int ac, char **av)
{
	t_vm			vm;

	if (ac == 1)
	{
		ft_putstr("./corewar [-v] [-dump nbr_cycles] [[-n number]");
		ft_return_error(" champion1.cor]");
	}
	defaults(&vm);
	parse_av(ac, av, &vm);
	(vm.nbrp < 1) ? ft_return_error("Not enough players.") : 0;
	intros(&vm);
	(vm.v & 1) ? visualizer(&vm) : start(&vm);
	return (0);
}
