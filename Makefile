# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/13 13:09:02 by jbarette          #+#    #+#              #
#    Updated: 2022/07/26 17:20:47 by jbarette         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

CFLAGS	=	-I ./Includes -I /opt/homebrew/Cellar/readline/8.1.2/include -g

SDIR	=	srcs

SRCS_C	=	main.c \
			init.c \
			parsing.c \
			handler_cmd.c \
			parsing_args.c \
			parsing_cmd.c \
			create_env.c \
			utils.c \
			utils2.c \
			ft_echo.c \
			ft_export.c \
			ft_cd.c \
			ft_unset.c \
			ft_env.c \
			ft_pwd.c \
			ft_expansion.c \
			ft_exit.c \
			fast_parsing.c \
			get_path.c \
			signals.c \
			ft_export1.c \
			parsing_args_save.c \

SRCS	=	$(patsubst %, $(SDIR)/%, $(SRCS_C))

ODIR	=	.objs
OBJS_O	=	$(SRCS_C:.c=.o)
OBJS	=	$(patsubst %, $(ODIR)/%, $(OBJS_O))

LDIR 	=	./libft
LIBFT 	=	libft/libft.a

all: $(NAME)

$(NAME): .objs $(OBJS)
	make -C $(LDIR)
	gcc $(CFLAGS) -lreadline -L /opt/homebrew/Cellar/readline/8.1.2/lib $(LIBFT) $(OBJS) -o $@

.objs:
	mkdir .objs

$(ODIR)/%.o: $(SDIR)/%.c
	gcc $(CFLAGS) -c $^ -o $@

clean:
	make -C $(LDIR) clean
	rm -f $(OBJS)
	rm -rf .objs

fclean: clean
	make -C $(LDIR) fclean
	rm -f $(NAME)

re: fclean all