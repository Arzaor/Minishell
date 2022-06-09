#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct		s_cmd
{
	char			**cmd;
	char			**opts;
	char			**args;
}					t_cmd;

void	start_minishell();
void	parsing_builtins(char *line);

#endif