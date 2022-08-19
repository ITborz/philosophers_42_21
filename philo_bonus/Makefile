# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/02 19:53:59 by bkristen          #+#    #+#              #
#    Updated: 2022/06/26 19:32:49 by bkristen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CC = cc

CFLAGS = -Wall -Werror -Wextra

INCLUDES_PATH = ./incl/

INCLUDES = $(INCLUDES_PATH)philo_bonus.h

PTHREAD 	= -lpthread

SRC_DIR = ./src/

OBJ_DIR = ./objects/

SRC_FILES = main.c \
			executer.c\
			utils.c \
			init.c \
			error.c

SRC	=	$(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ	= $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

all	:	temp $(NAME)

temp :
	@mkdir -p ./objects/

$(NAME):	$(OBJ)
			$(CC) $(OBJ) $(PTHREAD) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCLUDES) Makefile
	$(CC) $(CFLAGS) -I $(INCLUDES_PATH) -c $< -o $@

.PHONY : all clean fclean re

clean :
		@rm -rf $(OBJ_DIR)
		echo "\nzachistka\n"

fclean : 
		@rm -f $(NAME)
		@rm -rf $(OBJ_DIR)
		@echo "\npolnaya_zachistka\n"

re : fclean all
