# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgagnot <jgagnot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/13 09:59:01 by jgagnot           #+#    #+#              #
#    Updated: 2017/07/31 14:56:38 by tfontain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	@Make -C asm
	@Make -C vmfiles
	@echo " - Making the corewar project"

clean:
	@Make clean -C asm
	@Make clean -C vmfiles
	@echo " - Cleaning objs"
	@rm -f $(OBJS)

fclean: clean
	@Make fclean -C asm
	@Make fclean -C vmfiles
	@echo " - Cleaning asm and vm executables"
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re
