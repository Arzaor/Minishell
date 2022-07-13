# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/13 13:09:02 by jbarette          #+#    #+#              #
#    Updated: 2022/07/13 18:32:49 by jbarette         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell

SRC_DIR 	= 	srcs/
INC_DIR 	= 	includes/

SRC 		=	main.c \
				init.c \
				parsing.c \
				handler_cmd.c \
				parsing_args.c \
				parsing_heredoc.c \
				parsing_cmd.c \
				create_env.c \
				utils.c \
				utils2.c \
				ft_echo.c \
				ft_export.c \
				ft_cd.c \
				ft_unset.c \
				right_redir.c \
				left_redir.c \
				handler_redir.c \
				ft_env.c \
				ft_pwd.c \
				ft_expansion.c \
				ft_exit.c \
				fast_parsing.c \
				ft_check_quote.c \
				get_path.c \
				
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