#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>
# include <stdlib.h>
# include <curses.h>
# include <term.h>

void	start_minishell();
void	sig_handler(int signo);
void	parsing_builtins(char *line);
void	rl_replace_line(const char *text,int clear_undo);

#endif