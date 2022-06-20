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
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct	s_parser {
	char		*parser_cmd;
	int			parser_opt;
	char		*parser_args;
	int			parser_double_quote;
	int			parser_single_quote;
	int			parser_left_redir;
	int			parser_right_redir;
	char		*parser_heredoc;
}				t_parser;

typedef struct			s_element
{
	char				*value;
	struct s_element	*next;
}						t_element;

typedef struct			s_env
{
	t_element			*first;
}						t_env;

int			g_code;

void		rl_replace_line(const char *text,int clear_undo);

//PARSING
void		parsing_symbols(char *line, t_env *env);
t_parser	*parsing_cmd(char *line, t_parser *parser);
t_parser	*parsing_args(char *line, t_parser *parser);
t_parser	*parsing_opts(char *line, t_parser *parser);
t_parser	*parsing_heredoc(char *line, t_parser *parser);

//CMD
void	handler_cmd(t_parser *parser, t_env *env, char **cmds);
void	create_cmd(t_parser *parser, t_env *env);
void	ft_echo(t_parser *parser, t_env *env);
void	ft_cd(t_parser *parser);
void	ft_export(t_env *env,char *value);
void	ft_unset(t_env *env, char *arg);

//UTILS
int	ft_strcmp(const char *s1, const char *s2);
char	**create_tab(t_env *env);
void	free_array(char **array);
void ft_test(t_env *env,char *args);
// INIT & FREE
t_parser	*init();
void		free_parser(t_parser *parser);
t_env		*init_env();

// HANDLER LINKED LIST
void		display_linked_list(t_env *env);
t_env *create_env(char **env);
void		insert_env(t_env *env, char *value);
void		delete_env(t_env *env);
void		display_tab(char **env_tab);

#endif