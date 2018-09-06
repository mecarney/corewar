# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/21 18:11:36 by mjacques          #+#    #+#              #
#    Updated: 2018/08/29 15:26:13 by mjacques         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC							= gcc
RM							= rm -rf
NAME						= asm
FLAGS						= -Wall -Wextra -Werror
LIBFTLINK				= -L libftprintf/libft/ -lft
LIBFTPRINTF 		= libftprintf/lftprintf.a
LIBFTPRINTFLINK	= -L libftprintf/ -lftprintf
HEADER					= header/op.h\
									header/ft_asm.h\
									header/ft_struct.h\
									libftprintf/header/ft_printf.h\
									libftprintf/libft/header/libft.h

FILES 					= srcs/ft_asm.c\
									srcs/get_next_line.c\
									srcs/ft_file_struct.c\
									srcs/ft_print_op.c\
									srcs/ft_print_op_helper.c\
									srcs/ft_file_maker.c\
									srcs/ft_line_size.c\
									srcs/ft_error.c

OBJECTS					= $(FILES:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(OBJECTS): $(FILES)
	@echo -n 'Compiling asm...'
	@$(CC) $(FLAGS) -c $(FILES) -I $(HEADER)
	@mv *.o 	srcs/

libftprintf: $(LIBFTPRINTF)

$(LIBFTPRINTF):
	@make -C libftprintf

$(NAME): $(LIBFTPRINTF) $(OBJECTS)
	@$(CC) -o $(NAME) $(OBJECTS) $(LIBFTPRINTFLINK) $(LIBFTLINK)
	@echo "\t\t\033[32mDone!\033[0m"
	@echo "\033[33mReady to make champs!\033[0m"

clean:
	@$(RM) $(OBJECTS) $(HEADER:.h=.h.gch)
	@make clean -C libftprintf

fclean: clean
	@echo -n 'Cleaning  asm...'
	@$(RM) $(NAME)
	@echo "\t\t\033[31mDone!\033[0m"
	@make fclean -C libftprintf

re: fclean all
