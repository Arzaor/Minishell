# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hterras <hterras@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/09 14:51:09 by hterras           #+#    #+#              #
#    Updated: 2022/06/09 14:51:13 by hterras          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME 		= minishell

SRC_DIR 	= 	srcs/
INC_DIR 	= 	includes/

SRC 		=	main.c \
				parsing.c

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
