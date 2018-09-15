# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/10 19:23:19 by mjacques          #+#    #+#              #
#    Updated: 2018/09/12 22:29:21 by mjacques         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= gcc
RM			= rm -rf
NAME		= libftprintf
NAMELIB		= libftprintf.a
FLAGS		= -Wall -Wextra -Werror
LIBFTPATH	= libft
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

LFTFILES	= srcs/ft_atoi.c\
			  srcs/ft_bzero.c\
			  srcs/ft_isdigit.c\
			  srcs/ft_itoa_base.c\
			  srcs/ft_putchar.c\
			  srcs/ft_putstr.c\
			  srcs/ft_strappend.c\
			  srcs/ft_strcat.c\
			  srcs/ft_strchr.c\
			  srcs/ft_strcmp.c\
			  srcs/ft_strcpy.c\
			  srcs/ft_strdel.c\
			  srcs/ft_strdup.c\
			  srcs/ft_strjoin.c\
			  srcs/ft_strlen.c\
			  srcs/ft_strnew.c\
			  srcs/ft_wcharlen.c\
			  srcs/ft_wstrlen.c\

OBJECTS		= $(FILES:.c=.o)
LFTOBJECTS	= $(addprefix $(LIBFTPATH)/, $(LFTFILES:.c=.o))

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
	@ar rc $(NAMELIB) $(OBJECTS) $(LFTOBJECTS) $(LIBFT)
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
