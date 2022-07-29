/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:47:29 by hterras           #+#    #+#             */
/*   Updated: 2022/07/29 20:08:48 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_build_in(char *cmd)
{
	const char	*built_in[8];
	int			i;

	i = 0;
	built_in[0] = "echo";
	built_in[1] = "cd";
	built_in[2] = "pwd";
	built_in[3] = "export";
	built_in[4] = "unset";
	built_in[5] = "env";
	built_in[6] = "exit";
	built_in[7] = NULL;
	while (built_in[i])
	{
		if (!ft_strcmp(built_in[i], cmd))
			return (true);
		i++;
	}
	return (false);
}

static void	ft_exit_status(int status)
{
	if (WIFEXITED(status))
		g_code = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{	
		if (g_code == 2)
			g_code += 128;
		if (g_code == 3)
		{
			g_code += 128;
		}
	}
}

void	exec_cmd(t_parser *parser, char **cmds)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
		printf("Fork");
	if (!pid)
	{
		if (execve(parser->parser_cmd, cmds, NULL) == -1)
		{
			g_code = 127;
			printf("bash: %s: command not found\n", cmds[0]);
			exit(g_code);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		g_code = status;
		ft_exit_status(status);
	}
}

void	create_cmd(t_parser *parser, t_env *env)
{
	if (!ft_strncmp(parser->parser_cmd, "echo", 4))
		ft_echo(parser);
	if (!ft_strncmp(parser->parser_cmd, "cd", 2))
		ft_cd(parser, env);
	if (!ft_strncmp(parser->parser_cmd, "pwd", 3))
		pwd(env);
	if (!ft_strncmp(parser->parser_cmd, "export", 6))
		ft_export(env, parser->parser_args);
	if (!ft_strncmp(parser->parser_cmd, "unset", 5))
		ft_unset(env, parser->parser_args);
	if (!ft_strncmp(parser->parser_cmd, "env", 3))
		ft_env(env);
	if (!ft_strncmp(parser->parser_cmd, "exit", 3))
		ft_exit(parser);
}

void	handler_cmd(t_parser *parser, t_env *env, char *line)
{
	char	**cmds;
	if (g_code != 130 && g_code != 131)
	{
		signal(SIGQUIT, sig_handler2);
		signal(SIGINT, sig_handler2);
	}
	if (!parser->parser_error)
	{
		cmds = fast_parsing(line, parser);
		if (!is_build_in(parser->parser_cmd) && \
			cmds[0][0] != '/' && ft_strncmp(cmds[0], "./", 2) != 0)
			get_absolute_path(get_env(env, "PATH"), parser);
		if (is_build_in(parser->parser_cmd))
			create_cmd(parser, env);
		else
			exec_cmd(parser, cmds);
	}
}
