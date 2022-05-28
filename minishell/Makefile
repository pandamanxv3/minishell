# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/06 11:28:34 by cbarbit           #+#    #+#              #
#    Updated: 2022/05/28 04:24:37 by aboudjel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

C_FILES =	srcs/minishell.c \
			srcs/lexer_all.c \
			srcs/init_processes.c \
			srcs/env_lst.c \
			srcs/mallocs.c \
			srcs/signals_handlers.c \
			srcs/init_tokens.c \
			srcs/copy_tokens.c \
			srcs/manage_tokens.c \
			srcs/define_token_type.c \
			srcs/builtins.c \
			srcs/builtins_bis.c \
			srcs/builtins_in_action.c \
			srcs/exec.c \
			srcs/utils_exec.c \
			srcs/get_tab_exec.c
CC = cc

CFLAGS = -Werror -Wall -Wextra -g -g3 

RM = rm -f

O_FILES = ${C_FILES:.c=.o}

all: ${NAME}

%.o: %.c
	@${CC} ${CFLAGS} -c $< -o $@

${NAME} : ${O_FILES}
	@${MAKE} -C libft
	@${CC} ${O_FILES} -lreadline libft/libft.a -g -o ${NAME}


clean:
	@${RM} ${O_FILES}

fclean: clean
	@make fclean -C libft
	@${RM} ${NAME}


re: fclean all

.PHONY: all clean fclean re
