# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcarney <mcarney@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/14 17:21:31 by mcarney           #+#    #+#              #
#    Updated: 2018/09/14 17:36:32 by mcarney          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar_project
COREWAR = vm/corewar
ASM = asm/asm

.PHONY: all clean fclean re

all: $(NAME)

corewar: $(COREWAR)

$(COREWAR):
	@make -C vm

asm: $(ASM)

$(ASM):
	@make -C asm

$(NAME): $(COREWAR) $(ASM)

clean:
	@make clean -C vm
	@make clean -C asm

fclean: clean
	@make fclean -C vm
	@make fclean -C asm

re: fclean all
