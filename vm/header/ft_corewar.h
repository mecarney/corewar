/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_corewar.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 19:45:48 by mjacques          #+#    #+#             */
/*   Updated: 2018/09/14 16:56:59 by fhong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COREWAR_H
# define FT_COREWAR_H

# include <fcntl.h>
# include <ncurses.h>

# include "../../libftprintf/header/ft_printf.h"
# include "../../libftprintf/libft/header/libft.h"
# include "op.h"

# define UINT unsigned int
# define UCHAR unsigned char
# define REG(x) p->value_p[x] - 1
# define TIME_TO_DIE vm->ttd_cycles / MAX_CHECKS == vm->ctd || vm->ctd < 0

typedef struct		s_pro
{
	int				carry;
	int				reg[REG_NUMBER];
	int				pc;
	int				op_delay;
	unsigned char	op;
	unsigned int	owner;
	int				value_p[3];
	unsigned char	type_p[3];
	unsigned char	size_p[3];
	unsigned int	size_instruction;
	int				live;
	struct s_pro	*next;
}					t_process;

typedef struct		s_op
{
	char			*op_name;
	int				arg_nbr;
	int				param[3];
	int				opcode;
	int				cycles;
	char			*comment;
	int				is_coding_byte;
	int				truncation;
}					t_op;

typedef struct		s_player
{
	int				nbr;
	unsigned char	name[PROG_NAME_LENGTH + 4];
	unsigned char	comment[COMMENT_LENGTH + 4];
	unsigned int	size;
	unsigned char	code[CHAMP_MAX_SIZE];
	int				reg[REG_NUMBER];
}					t_player;

typedef struct		s_vm
{
	t_process		*pro_lst;
	unsigned int	nbr_of_processes;
	unsigned char	arena[MEM_SIZE];
	unsigned char	territory[MEM_SIZE];

	int				ctd;
	unsigned int	dump_cycle;
	unsigned int	vm_cycle;
	unsigned int	new_cycles;
	unsigned int	ttd_cycles;
	unsigned int	cycle_to_die;

	unsigned int	nbrp;
	unsigned int	player_alive[MAX_PLAYERS];
	unsigned int	last_live[MAX_PLAYERS];
	t_player		p[MAX_PLAYERS];
	unsigned int	nbr_lives;

	unsigned int	v : 1;
}					t_vm;

typedef void		(*t_func)(t_vm *vm, t_process *p);

typedef struct		s_op_dispatch
{
	int				op_code;
	t_func			fct;
}					t_op_dispatch;

# define OP_NUMBER 17

extern t_op_dispatch	g_dispatch[OP_NUMBER];
extern t_op				g_tab[OP_NUMBER];

void				new_p(char **av, int i, t_vm *vm);
void				new_pn(char **av, int i, t_vm *vm);
void				print_arena(t_vm *v);
void				pushfront_process(t_process **alst, t_process *new);
t_process			*new_pro(t_process *old, int pc);
void				free_processes(t_process **pro_lst);
void				start(t_vm *vm);
void				execute_processes(t_process *pro_lst, t_vm *vm);
void				intros(t_vm *vm);

/*
**	ft_decode.c
*/

int					ft_instruction_edge(t_process *p, UCHAR op);
int					ft_instruction(t_process *p, UCHAR op, UCHAR op_type);
void				ft_add_param(t_process *p, UCHAR *arena, int op_code);
void				ft_init_player(t_process *p);
int					ft_decode(t_process *p, UCHAR *arena);

/*
**	ft_functions.c
*/

void				ft_param(int *param, UCHAR *arena, int pc, int size);
int					ft_check_param(t_process *p, UCHAR op);
void				ft_putarena(UINT param, t_vm *vm, int pc, t_process *pro);
int					ft_return_error(char const *str);
int					modify_pc(int pc);

/*
**	ft_execute_0x00-0x04.c
*/

void				ft_null(t_vm *vm, t_process *p);
void				ft_live(t_vm *vm, t_process *p);
void				ft_load(t_vm *vm, t_process *p);
void				ft_long_load(t_vm *vm, t_process *p);
void				ft_store(t_vm *vm, t_process *p);
void				ft_store_index(t_vm *vm, t_process *p);
void				ft_addition(t_vm *vm, t_process *p);
void				ft_substraction(t_vm *vm, t_process *p);
void				ft_and(t_vm *vm, t_process *p);
void				ft_or(t_vm *vm, t_process *p);
void				ft_xor(t_vm *vm, t_process *p);
void				ft_zjump(t_vm *vm, t_process *p);
void				ft_load_index(t_vm *vm, t_process *p);
void				ft_long_load_index(t_vm *vm, t_process *p);
t_process			*ft_fork_player(t_process *p, int idx);
void				ft_fork(t_vm *vm, t_process *p);
void				ft_long_fork(t_vm *vm, t_process *p);
void				ft_aff(t_vm *vm, t_process *p);

void				visualizer(t_vm *vm);
void				decorate_win(t_vm *vm);
void				kill_processes(t_process **pro_lst, UINT *nbrpro);
void				base(t_vm *vm);

#endif
