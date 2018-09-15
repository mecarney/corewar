# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcarney <mcarney@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/14 17:21:31 by mcarney           #+#    #+#              #
#    Updated: 2018/09/15 10:15:48 by mcarney          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar_project
ASM = asm/asm
COREWAR = vm/corewar

.PHONY: all clean fclean re

all: $(NAME)

asm: $(ASM)

$(ASM):
	@make -C asm

corewar: $(COREWAR)

$(COREWAR):
	@make -C vm

$(NAME): $(ASM) $(COREWAR)

clean:
	@make clean -C vm
	@make clean -C asm

fclean: clean
	@make fclean -C vm
	@make fclean -C asm

re: fclean all
