NAME	=	minishell

FLAGS	=	-Wall -Werror -Wextra -I ./includes -I ~/.brew/opt/readline/include -g

SRCS	=	srcs/main.c

OBJS	=	$(SRCS:.c=.o)

LDIR	=	./libft
LIBFT	=	libft/libft.a

all: $(NAME)

$(NAME): $(OBJS)
		make -C $(LDIR)
		gcc $(FLAGS) -lreadline -L ~/.brew/opt/readline/lib $(LIBFT) $(OBJS) -o $@

$(OBJS): $(SRCS)
	gcc $(FLAGS) -c $^ -o $@

clean:
	make -C $(LDIR) clean
	rm -f $(OBJS)
	rm -rf .objs

fclean: clean
	make -C $(LDIR) fclean
	rm -f $(NAME)

re: fclean all