# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 16:29:22 by rleskine          #+#    #+#              #
#    Updated: 2023/06/16 12:47:17 by rleskine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo
#BONUS		=	checker
SRC			=	philo_utils1.c
OBJ			=	$(SRC:.c=.o)
CFLAGS		=	-Wall -Wextra -Werror -pthread
# -fsanitize=address
# remove fsanitize to make leaks work
NPROCS 		=	$(shell sysctl hw.ncpu | grep -o '[0-9]\+')


CC =	cc

all: $(NAME)

$(NAME): %: %.c $(OBJ)
	$(CC) $(CFLAGS) -o $@ $< $(OBJ)

$(OBJ): %.o: %.c
	@echo "\033[2K [$(NAME)]: Compilation of $< \033[A"
	$(CC) $(CFLAGS) -c -o $@ $<

#bonus: $(BONUS)

#$(BONUS): %: %.c $(OBJ)
#	$(CC) $(CFLAGS) $(GFX) $(INCLUDE) $(LIBFLAGS) -o $@ $< $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	/bin/rm -f $(NAME) $(BONUS)

re: fclean all

#.SILENT:
