# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/01 11:56:43 by chchao            #+#    #+#              #
#    Updated: 2022/06/13 12:06:45 by jbarette         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME 		= minishell

SRC_DIR 	= 	srcs/
INC_DIR 	= 	includes/

SRC 		=	main.c \
				lexer.c

SRCS 		= 	$(addprefix ${SRC_DIR}, ${SRC})
SRCS_ALL 	= 	${SRCS}

OBJS 		= 	$(SRCS:.c=.o)

CC			= 	gcc
CFLAGS		=	-Wall -Wextra -Werror

LIB_RDL 	= 	libreadline.a ./libft/libft.a

%.o: %.c
		${CC} $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(NAME): $(OBJS)
		make -C ./libft
		cp ./readline/libreadline.a ./
		${CC} $(CFLAGS) $(OBJS) ${LIB_RDL} -lncurses -o $(NAME)

all:
		$(MAKE) -j $(NAME)

clean:
		make -C ./libft clean
		rm -rf $(OBJS)

fclean:	clean
		make -C ./libft fclean
		rm -rf $(NAME)
		rm -rf libreadline.a

re: fclean all

.PHONY: all, clean, fclean, re
