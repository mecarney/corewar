# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/10 19:23:19 by mjacques          #+#    #+#              #
#    Updated: 2018/09/15 14:11:17 by mcarney          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= gcc
RM			= rm -rf
NAME		= libftprintf
NAMELIB		= libftprintf.a
FLAGS		= -Wall -Wextra -Werror
LIBFT 		= $(addprefix $(LIBFTPATH)/, libft.a)
HEADER		= header/ft_printf.h\
			  libft/header/libft.h
FILES 		= srcs/ft_printf.c\
			  srcs/ft_arguments.c\
			  srcs/ft_converser_1.c\
			  srcs/ft_converser_2.c\
			  srcs/ft_converser_3.c\
			  srcs/ft_converser_free.c\
			  srcs/ft_converser_width.c\
			  srcs/ft_converser_precision.c

OBJECTS		= $(FILES:.c=.o)

.PHONY: all clean fclean re

all: $(NAMELIB)

$(OBJECTS): $(FILES)
	@echo -n 'Compiling $(NAME)...'
	@$(CC) $(FLAGS) -c $(FILES) -I $(HEADER)
	@mv *.o srcs/

libft: $(LIBFT)

$(LIBFT):
	@make -C libft

$(NAMELIB): $(LIBFT) $(OBJECTS)
	@ar rc $(NAMELIB) $(OBJECTS)
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
