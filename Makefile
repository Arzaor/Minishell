# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/13 13:09:02 by jbarette          #+#    #+#              #
#    Updated: 2022/08/06 13:25:31 by jbarette         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	minishell

SRC_DIR 	= 	srcs/
INC_DIR 	= 	includes/

SRC 		=	create_env.c \
				fast_parsing.c \
				ft_cd.c \
				ft_echo.c \
				ft_env.c \
				ft_exit.c \
				ft_export.c \
				ft_pwd.c \
				ft_unset.c \
				get_env.c \
				get_env_cmd.c \
				get_path.c \
				handler_cmd.c \
				init.c \
				main.c \
				parsing_args_save.c \
				parsing_cmd_save.c \
				parsing_args_save1.c \
				parsing_cmd_save1.c \
				parsing_args.c \
				parsing_args1.c \
				parsing.c \
				signals.c \
				parsing_cmd.c \
				parsing_cmd1.c \
				utils.c \
				utils2.c \
				utils3.c \
				transform_arg.c \
				export_arg.c \
				count_cursor.c \
				transform_cmd.c \
				exec_cmd.c \
				
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