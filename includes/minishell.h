/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:55:50 by hterras           #+#    #+#             */
/*   Updated: 2022/08/01 11:42:17 by jbarette         ###   ########.fr       */
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
	int			parser_sig;
	int			parser_count;
	int			parser_error;
	char		*parser_pwd;
	char		*parser_arguments;
	int			parser_count_arg;
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
void	parsing_handler(t_parser *parser, char *line, \
						t_env *env);
t_parser	*parsing_cmd(char *line, t_parser *parser);
t_parser	*parsing_args(char *line, t_parser *parser, t_env *env);
t_parser	*parsing_opts(char *line, t_parser *parser);
char		*get_env(t_env *env, char *search);
void		get_absolute_path(char *path, t_parser *parser);
void		ft_exit_with_line(char *line);
void		get_absolute_path(char *path, t_parser *parser);
void		save_to_arg(t_parser *parser, t_env *env);
int			found_second_quote(t_parser *parser, int i, char quote, t_env *env);
int			found_second_quote_save(t_parser *parser, int i, \
				char quote, t_env *env);

//EXPORT
void		export_arg(t_env *env, char *value);
void		ft_tri_tab(char **tri, int count);

//PROMPT
void		show_prompt(char *line, t_env *envp);
void		rl_replace_line(const char *text, int clear_undo);

//CMD
void		handler_cmd(t_parser *parser, t_env *env, char *line);
void		create_cmd(t_parser *parser, t_env *env);
void		ft_echo(t_parser *parser);
void		ft_cd(t_parser *parser, t_env *env);
void		ft_export(t_env *env, char *value);
void		ft_unset(t_env *env, char *arg);
void		ft_env(t_env *env);
void		pwd(t_env *env);
void		exec_cmd(t_parser *parser, char **cmds);
void		ft_exit(t_parser *parser);
int			count_cursor(t_parser *parser, char *line);
int			count_option(char *line, int i);

//SIGNALS
void		init_signals(void);

//UTILS
int			ft_strcmp(const char *s1, const char *s2);
char		**create_tab(t_env *env);
void		free_array(char **array);
bool		is_build_in(char *cmd);
char		*ft_strcat(char *dest, char *src);

// INIT & FREE
t_parser	*init(void);
void		free_parser(t_parser *parser);
t_env		*init_env(void);

// HANDLER LINKED LIST
void		display_linked_list(t_env *env);
t_env		*create_env(char **env);
int			insert_env(t_env *env, char *value);
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
void		style_prompt(void);
char		**fast_parsing(char *line, t_parser *parser);
int			ft_isalnum(int c);
int			char_is_var_attribution(char *str);
int			get_var_env(t_parser *parser, int i, t_env *env, int count);

#endif