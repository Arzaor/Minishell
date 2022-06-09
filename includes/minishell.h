#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>

void	start_minishell();
void	crtl_c();

#endif