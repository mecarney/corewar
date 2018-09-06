# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/29 17:14:25 by mjacques          #+#    #+#              #
#    Updated: 2018/08/29 15:37:07 by mjacques         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				= gcc
RM				= rm -rf
NAME			= libftprintf
NAMELIB		= libftprintf.a
FLAGS			= -Wall -Wextra -Werror
LIBFT 		= libft/libft.a
LIBFTLINK	= -L libft/ -lft
HEADER		= header/ft_printf.h\
						libft/header/libft.h
FILES 		= srcs/ft_printf.c\
						srcs/ft_arguments.c\
						srcs/ft_converser_c_s.c\
						srcs/ft_converser_o_u_x.c\
						srcs/ft_converser_void_di.c\
						srcs/ft_converser_helper.c\
						srcs/ft_helperfunctions.c

OBJECTS		= $(FILES:.c=.o)

.PHONY: all clean fclean re

all: $(NAMELIB)

$(OBJECTS): $(FILES)
	@echo -n 'Compiling $(NAME)...'
	@$(CC) $(FLAGS) -c $(FILES) -I $(HEADER)
	@mv *.o 	srcs/

libft: $(LIBFT)

$(LIBFT):
	@make -C libft

$(NAMELIB): $(LIBFT) $(OBJECTS)
	@ar rc $(NAMELIB) $(OBJECTS) $(LIBFT)
	@ranlib $(NAMELIB)
	@echo "\t\033[32mDone!\033[0m"

clean:
	@$(RM) $(OBJECTS) $(HEADER:.h=.h.gch)
	@make clean -C libft

fclean: clean
	@echo -n 'Cleaning  $(NAME)...'
	@$(RM) $(NAMELIB)
	@echo "\t\033[31mDone!\033[0m"
	@make fclean -C libft

re: fclean all
