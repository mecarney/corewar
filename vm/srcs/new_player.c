/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarney <mcarney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 10:41:46 by mcarney           #+#    #+#             */
/*   Updated: 2018/09/05 09:25:24 by mcarney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_corewar.h"
#include <stdio.h>

/*
** Validate cor file and champion size.
*/

void				validate_p(char *file)
{
	int			fd;

	if (!file || ft_strcmp(file + ft_strlen(file) - 4, ".cor"))
		ft_return_error("Error: file has an invalid header");
	if ((fd = open(file, O_RDONLY)) != -1)
	{
		if (lseek(fd, 0, SEEK_END) - sizeof(t_header) > CHAMP_MAX_SIZE)
			ft_return_error("Error: file has too large a code");
	}
	else
		ft_return_error("Error: can't read source file");
	close(fd);
}

/*
** Store each player in the t_vm struct which has a array of player structs
** that should probably be malloced but I took a lazy route. TODO: check magic.
*/

void				store_p(char *file, t_vm *vm, int nbr)
{
	int				fd;
	int				size;
	// unsigned int	magic[4];

	if ((fd = open(file, O_RDONLY)) != -1)
	{
		lseek(fd, 4, SEEK_CUR);
		// read(fd, &magic[3], 1);
		// read(fd, &magic[2], 1);
		// read(fd, &magic[1], 1);
		// read(fd, &magic[0], 1);
		// ft_printf(" %x %x %x %x | %x\n", magic[3], magic[2], magic[1], magic[0], COREWAR_EXEC_MAGIC);
		// if (*(unsigned int *)magic != COREWAR_EXEC_MAGIC)
		// 	ft_return_error("Error: incorrect magic number");
		size = read(fd, &(vm->players[nbr].name), PROG_NAME_LENGTH + 4);
		vm->players[nbr].name[size] = '\0';
		lseek(fd, 4, SEEK_CUR);
		size = read(fd, &(vm->players[nbr].comment), COMMENT_LENGTH + 4);
		vm->players[nbr].comment[size] = '\0';
		size = read(fd, &(vm->players[nbr].code), CHAMP_MAX_SIZE);
		vm->players[nbr].code[size] = '\0';
		vm->players[nbr].size = size;
		vm->players[nbr].nbr = nbr + 1;
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
	if (vm->players[nbr - 1].size)
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
	while (j < MAX_PLAYERS && vm->players[j].size)
		j++;
	validate_p(av[i]);
	(++vm->nbrp > MAX_PLAYERS) ? ft_return_error("Error: too many players") : 0;
	store_p(av[i], vm, j);
}
