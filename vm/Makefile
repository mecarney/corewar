# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcarney <mcarney@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/29 10:41:39 by mcarney           #+#    #+#              #
#    Updated: 2018/09/04 13:54:06 by mcarney          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC							= gcc
RM							= rm -rf
NAME						= corewar
FLAGS						= -Wall -Wextra -Werror
LIBFTLINK				= -L libftprintf/libft/ -lft
LIBFTPRINTF 		= libftprintf/lftprintf.a
LIBFTPRINTFLINK	= -L libftprintf/ -lftprintf
API							= -lncurses
HEADER					= header/op.h\
									header/ft_corewar.h\
									libftprintf/header/ft_printf.h\
									libftprintf/libft/header/libft.h

FILES 					= srcs/main.c\
									srcs/new_player.c\
									srcs/arena.c\
									srcs/processes.c\
									srcs/visualizer.c\
									srcs/ft_decode.c\
									srcs/ft_functions.c\
									srcs/ft_execute_0x04.c\
									srcs/ft_execute_0x09.c\
									srcs/ft_execute_0x0e.c\
									srcs/ft_execute_0x10.c

OBJECTS					= $(FILES:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(OBJECTS): $(FILES)
	@echo -n 'Compiling $(NAME)...'
	@$(CC) $(FLAGS) -c $(FILES) -I $(HEADER)
	@mv *.o 	srcs/

libftprintf: $(LIBFTPRINTF)

$(LIBFTPRINTF):
	@make -C libftprintf

$(NAME): $(LIBFTPRINTF) $(OBJECTS)
	@$(CC) -o $(NAME) $(OBJECTS) $(API) $(LIBFTPRINTFLINK) $(LIBFTLINK) -g -fsanitize=address
	@echo "\t\t\033[32mDone!\033[0m"
	@echo "\033[33mPrepare your champs, it's time to fight!\033[0m"

clean:
	@$(RM) $(OBJECTS) $(HEADER:.h=.h.gch)
	@make clean -C libftprintf

fclean: clean
	@echo -n 'Cleaning  $(NAME)...'
	@$(RM) $(NAME)
	@echo "\t\t\033[31mDone!\033[0m"
	@make fclean -C libftprintf

re: fclean all