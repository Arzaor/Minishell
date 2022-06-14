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

typedef struct	s_parser {
	char	*parser_cmd;
	int		parser_opt;
	char	*parser_args;
	int		parser_double_quote;
	int		parser_single_quote;
	int		parser_left_redir;
	int		parser_right_redir;
	char	*parser_heredoc;
}				t_parser;

typedef struct		s_data
{
	t_parser		parser;
	struct t_data	*next;
}					t_data;

void		rl_replace_line(const char *text,int clear_undo);
void		parsing_symbols(char *line,char **env);
t_parser	*parsing_cmd(char *line, t_parser *parser);
t_parser	*parsing_args(char *line, t_parser *parser);
t_parser	*parsing_opts(char *line, t_parser *parser);
t_parser	*parsing_heredoc(char *line, t_parser *parser);
t_parser	*init();
void		handler_cmd(t_parser *parser, char **env);

#endif