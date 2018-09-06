/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_corewar.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 19:45:48 by mjacques          #+#    #+#             */
/*   Updated: 2018/09/04 16:41:59 by mcarney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COREWAR_H
# define FT_COREWAR_H

# include <fcntl.h>
# include <ncurses.h>

# include "../libftprintf/header/ft_printf.h"
# include "../libftprintf/libft/header/libft.h"
# include "op.h"

# define UINT unsigned int
# define UCHAR unsigned char
# define REG(x) p->value_p[x] - 1

typedef struct			s_process
{
	int					carry;
	int					reg[REG_NUMBER];
	int					pc;
	int					op_delay;
	unsigned char		next_op;
	unsigned int		owner;
	int					value_p[3]; //Param of the actual process
	unsigned char		type_p[3]; //Type of param of the actu process
	unsigned char		size_p[3]; //Size of the param
	unsigned int		size_instruction; //Size between the 2 instructions
	int							nbr; //process nbr <== Delete
	int					live;
	struct s_process	*next;
}					t_process;

typedef struct			s_op
{
	char				*op_name; //Literal name
	int					arg_nbr; //Number of Argument
	int					param[3]; //Types of parameters
	int					opcode; //Value
	int					cycles; //Number of cycles
	char				*comment;
	int					is_coding_byte;
	int					truncation;
}						t_op;

typedef struct			s_player
{
	int		nbr;	//Player number
	unsigned char		name[PROG_NAME_LENGTH + 4];
	unsigned char		comment[COMMENT_LENGTH + 4];
	unsigned int		size; //Size of the player (Without the header)
	unsigned char		code[CHAMP_MAX_SIZE]; //Program (Without the header)
	// unsigned int		value_p[3]; //Param of the actual process
	// unsigned char		type_p[3]; //Type of param of the actu process
	// unsigned char		size_p[3]; //Size of the param
	// unsigned int		size_instruction; //Size between the 2 instructions

	int		reg[REG_NUMBER]; //Registers
	// int					carry : 1;
	// unsigned int		p_cycle; //Cycles of the player
}						t_player;

typedef struct			s_vm
{
	t_process			*pro_lst;
	unsigned int		nbr_of_processes;
	unsigned char		arena[MEM_SIZE]; //Arena "stack"
	unsigned char		territory[MEM_SIZE];

	int							ctd;
	unsigned int		dump_cycle;
	unsigned int		vm_cycle; // Cycle of the VM
	unsigned int		new_cycles; //cycles since last cycle to die
	unsigned int		cycle_to_die; // Cycle before to Die

	unsigned int		nbrp; //Nbr players for matt :)
	unsigned int		player_alive[MAX_PLAYERS]; //Should we use a int : 1? We juste need to know if it is alive
	unsigned char		last_live[MAX_PLAYERS]; //Array of size Players, each player change the cycle when the last live append
	t_player				players[MAX_PLAYERS];

	unsigned int		v : 1; //visualizer flag
}									t_vm;

typedef void			(*t_func)(t_vm *vm, t_process *p);

typedef struct		s_op_dispatch
{
	int							op_code;
	t_func				fct;
}									t_op_dispatch;

# define OP_NUMBER 17

extern t_op_dispatch	g_dispatch[OP_NUMBER];
extern t_op				g_tab[OP_NUMBER];

void			new_p(char **av, int i, t_vm *vm);
void			new_pn(char **av, int i, t_vm *vm);
void			print_arena(t_vm *v);
void			pushfront_process(t_process **alst, t_process *new);
t_process		*new_process(t_process *old, int pc, int idx);
void			free_processes(t_process **pro_lst);
void			start(t_vm *vm);
void			execute_processes(t_process *pro_lst, t_vm *vm);

/*
**	ft_decode.c
*/
int				ft_instruction_edge(t_process *p, UCHAR op);
int				ft_instruction(t_process *p, UCHAR op, UCHAR op_type);
void			ft_add_param(t_process *p, UCHAR *arena, int op_code);
void			ft_init_player(t_process *p);
int				ft_decode(t_process *p, UCHAR *arena);

/*
**	ft_functions.c
*/
void			ft_param(int *param, UCHAR *arena, int pc, int size);
int				ft_check_param(t_process *p, UCHAR op);
void			ft_putarena(UINT param, t_vm *vm, int pc, t_process *pro);
int				ft_return_error(char const *str);
int				modify_pc(int pc);

/*
**	ft_execute_0x00-0x04.c
*/
void			ft_null(t_vm *vm, t_process *p);
void			ft_live(t_vm *vm, t_process *p);
void			ft_load(t_vm *vm, t_process *p);
void			ft_long_load(t_vm *vm, t_process *p);
void			ft_store(t_vm *vm, t_process *p);
void			ft_store_index(t_vm *vm, t_process *p);
void			ft_addition(t_vm *vm, t_process *p);
void			ft_substraction(t_vm *vm, t_process *p);
void			ft_and(t_vm *vm, t_process *p);
void			ft_or(t_vm *vm, t_process *p);
void			ft_xor(t_vm *vm, t_process *p);
void			ft_zjump(t_vm *vm, t_process *p);
void			ft_load_index(t_vm *vm, t_process *p);
void			ft_long_load_index(t_vm *vm, t_process *p);
t_process		*ft_fork_player(t_process *p, int idx);
void			ft_fork(t_vm *vm, t_process *p);
void			ft_long_fork(t_vm *vm, t_process *p);
void			ft_aff(t_vm *vm, t_process *p);


void				visualizer(t_vm *vm);
void				decorate_win(t_vm *vm);
void			kill_processes(t_process **pro_lst, UINT *nbrpro);
void 			base(t_vm *vm);

#endif
