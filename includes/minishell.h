/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hterras <hterras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:55:50 by hterras           #+#    #+#             */
/*   Updated: 2022/07/21 18:15:02 by hterras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <errno.h>

# define CTRL_C SIGINT

typedef struct s_parser {
	char		*parser_cmd;
	int			parser_opt;
	char		*parser_args;
	int			parser_double_quote;
	int			parser_single_quote;
	int			parser_left_redir;
	int			parser_right_redir;
	int			parser_dleft_redir;
	int			parser_dright_redir;
	int			parser_sig;
	char		*parser_heredoc;
	char		*parser_pwd;
}				t_parser;

typedef struct s_element
{
	char				*value;
	struct s_element	*next;
}						t_element;

typedef struct s_env
{
	t_element			*first;
}						t_env;

int			g_code;

//PARSING
void		parsing_symbols(t_parser *parser, char *line, t_env *env);
t_parser	*parsing_cmd(char *line, t_parser *parser);
t_parser	*parsing_args(char *line, t_parser *parser, t_env *env);
t_parser	*parsing_opts(char *line, t_parser *parser);
t_parser	*parsing_heredoc(char *line, t_parser *parser);
char		*get_env(t_env *env, char *search);
void		get_absolute_path(char *path, t_parser *parser);
void		ft_exit_with_line(char *line);
int			check_quote_redir(char *line, int i);
void		format_quotes(void);
int			ft_check_quote(t_parser *parser, int i, char quote, t_env *env);
int			ft_append_value(t_parser *parser, int s, char quote, t_env *env);
void		get_absolute_path(char *path, t_parser *parser);
char		*check_dollars1(int count, int i, char *env_var, t_parser *parser);
int			check_symbols(t_parser *parser, int i);
int			ft_count_i1(char *line, int i, int count, t_parser *parser);
int			ft_count_i(t_parser *parser, char *line);

//EXPORT
void		export_arg(t_env *env, char *value);
char		*check_symbols_w_parser(char *str, int i);
void		export_arg2(t_env *env, char *value);
void		ft_tri_tab(char **tri, int count);
char		*search_expansion(char **split_equals);
void		export_w_expansion(t_env *env, char **split_equals, \
				char **split_space, int i);
void		concat_expansion(char **split_equals, char *result, t_env *env);
int			check_dollars_w_quote(t_parser *parser, int i, t_env *env);

//PROMPT
void		show_prompt(char *line, t_env *envp);
void		rl_replace_line(const char *text, int clear_undo);

//CMD
void		handler_cmd(t_parser *parser, t_env *env, char **cmds);
void		create_cmd(t_parser *parser, t_env *env);
void		ft_echo(t_parser *parser, t_env *env);
void		ft_cd(t_parser *parser, t_env *env);
void		ft_export(t_env *env, char *value);
void		ft_unset(t_env *env, char *arg);
void		ft_env(t_env *env);
void		pwd(t_env *env);
void		exec_cmd(t_parser *parser, char **cmds);
void		ft_exit(t_parser *parser);

//SIGNALS
void		init_signals(void);

//UTILS
int			ft_strcmp(const char *s1, const char *s2);
char		**create_tab(t_env *env);
void		free_array(char **array);
void		ft_test(t_env *env, char *args);
bool		is_build_in(char *cmd);
char		*ft_strcat(char *dest, char *src);

// INIT & FREE
t_parser	*init(void);
void		free_parser(t_parser *parser);
t_env		*init_env(void);

// HANDLER LINKED LIST
void		display_linked_list(t_env *env);
t_env		*create_env(char **env);
void		insert_env(t_env *env, char *value);
void		delete_env(t_env *env);
void		display_tab(char **env_tab);
char		*test(char **tab_env, int i);

//SIGNAUX
void		signal_handler3(int sig);
void		signal_handler_2(int sig);
void		set_signal(int sig);
void		sig_handler2(int sig);
void		kill_process(int *process);

//REDIR
int			handler_dright_redir(t_parser *parser);
void		handler_redir(t_parser *parser, char **cmds, t_env *env);
int			handler_right_redir(t_parser *parser);
int			handler_left_redir(char *heredoc);
int			handler_dleft_redir(t_parser *parser);
int			check_dollars(t_parser *parser, int i, t_env *env);
void		style_prompt(void);
t_parser	*parsing_cmd(char *line, t_parser *parser);
void		clean_redir(t_parser *parser, int saveout1);
char		**fast_parsing(t_parser *parser, char *line);
void		sig_handler(int signo);

#endif