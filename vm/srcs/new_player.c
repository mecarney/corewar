/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarney <mcarney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 10:41:46 by mcarney           #+#    #+#             */
/*   Updated: 2018/09/19 11:05:39 by mcarney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_corewar.h"

/*
** Introduce all players and place them in the arena.
*/

void				intros(t_vm *vm)
{
	int				i;
	unsigned int	x;
	unsigned int	pc;
	unsigned int	y;

	i = -1;
	y = 0;
	ft_putendl("Introducing contestants...");
	while (++i < MAX_PLAYERS)
		if (vm->p[i].size)
		{
			pc = MEM_SIZE / vm->nbrp * y++;
			ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
				vm->p[i].nbr, vm->p[i].size, vm->p[i].name, vm->p[i].comment);
			ft_memcpy((char *)(vm->arena + pc), vm->p[i].code, vm->p[i].size);
			x = 0;
			while (x < vm->p[i].size)
				vm->territory[pc + x++] = vm->p[i].nbr;
			pushfront_process(&(vm->pro_lst), new_pro(NULL, vm->arena[pc]));
			vm->pro_lst->reg[0] = vm->p[i].nbr * -1;
			vm->pro_lst->owner = vm->p[i].nbr;
			vm->pro_lst->pc = pc;
			vm->pro_lst->op_delay = g_tab[vm->arena[pc]].cycles - 1;
			vm->nbr_of_processes++;
		}
}

/*
** Validate cor file and champion size.
*/

void				validate_p(char *file)
{
	int				fd;

	if (!file || ft_strcmp(file + ft_strlen(file) - 4, ".cor"))
		ft_return_error("Error: file has an invalid header");
	if ((fd = open(file, O_RDONLY)) != -1)
	{
		if (lseek(fd, 0, SEEK_END) - sizeof(t_header) > CHAMP_MAX_SIZE)
			ft_return_error("Error: file is too large");
	}
	else
		ft_return_error("Error: can't read source file");
	close(fd);
}

/*
** Store each player in the t_vm struct which has a array of player structs
** and validate magic_number.
*/

void				store_p(char *file, t_vm *vm, int nbr)
{
	int				fd;
	int				size;
	unsigned char	magic_number[4];

	if ((fd = open(file, O_RDONLY)) != -1)
	{
		read(fd, &magic_number[3], 1);
		read(fd, &magic_number[2], 1);
		read(fd, &magic_number[1], 1);
		read(fd, &magic_number[0], 1);
		if (*(unsigned int *)magic_number != COREWAR_EXEC_MAGIC)
			ft_return_error("Error: invalid magic_number");
		read(fd, &(vm->p[nbr].name), PROG_NAME_LENGTH + 4);
		if (!(vm->p[nbr].name[0]))
			ft_return_error("Error: Champ needs a name");
		lseek(fd, 4, SEEK_CUR);
		read(fd, &(vm->p[nbr].comment), COMMENT_LENGTH + 4);
		size = read(fd, &(vm->p[nbr].code), CHAMP_MAX_SIZE);
		(size) ? vm->p[nbr].size = size :
			ft_return_error("Error: invalid Champ size");
		vm->p[nbr].nbr = nbr + 1;
	}
	else
		ft_return_error("Error: can't read source file");
	close(fd);
}

/*
** Add a player after the -n arg, check that the number doesn't already exist,
** validate player, and store player.
*/

void				new_pn(char **av, int i, t_vm *vm)
{
	unsigned int	nbr;

	nbr = ft_atoi(av[i + 1]);
	if (vm->p[nbr - 1].size)
		ft_return_error("Error: -n player number already exists");
	validate_p(av[i + 2]);
	(++vm->nbrp > MAX_PLAYERS) ? ft_return_error("Error: too many players") : 0;
	store_p(av[i + 2], vm, nbr - 1);
}

/*
** Add a player without the -n arg, check that the number doesn't already exist
** (which would only occur because of an earlier -n), validate player,
** and store player.
*/

void				new_p(char **av, int i, t_vm *vm)
{
	unsigned int	j;

	j = 0;
	while (j < MAX_PLAYERS && vm->p[j].size)
		j++;
	validate_p(av[i]);
	(++vm->nbrp > MAX_PLAYERS) ? ft_return_error("Error: too many players") : 0;
	store_p(av[i], vm, j);
}
