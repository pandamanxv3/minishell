# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/03 03:43:32 by cbarbit           #+#    #+#              #
#    Updated: 2022/06/03 06:53:17 by cbarbit          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

C_FILES =	srcs/minishell.c \
			srcs/lexer_parser/lexer_all.c \
			srcs/lexer_parser/init_processes.c \
			srcs/lexer_parser/env_lst.c \
			srcs/lexer_parser/mallocs.c \
			srcs/lexer_parser/signals_handlers.c \
			srcs/lexer_parser/init_tokens.c \
			srcs/lexer_parser/copy_tokens.c \
			srcs/lexer_parser/manage_tokens.c \
			srcs/lexer_parser/define_token_type.c \
			srcs/lexer_parser/builtins_bis.c \
			srcs/exec/execution.c \
			srcs/exec/utils_exec.c \
			srcs/exec/here_doc.c \
			srcs/exec/gestion_fd.c \
			srcs/exec/get_tab_exec2.c \
			srcs/built-in/built_in_dispatcher.c \
			srcs/built-in/export.c \
			srcs/built-in/exit.c \
			srcs/built-in/env.c \
			srcs/built-in/echo.c \
			srcs/built-in/unset.c \
			srcs/exec/get_tab_exec.c
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