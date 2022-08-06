/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 13:13:46 by jbarette          #+#    #+#             */
/*   Updated: 2022/08/06 13:25:43 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_check_num(t_parser *parser)
{
	char	**split_space;

	split_space = ft_split(parser->parser_args, ' ');
	printf("exit\n");
	printf("bash: exit: %s: numeric argument required\n", \
		split_space[0]);
	g_code = 255;
	free_array(split_space);
	free_parser(parser);
	exit(g_code);
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

void	execve_error(t_parser *parser, t_env *env)
{
	if (chdir(parser->parser_cmd) == 0)
	{
		printf("bash: %s: is a directory\n", parser->parser_cmd);
		chdir(get_env(env, "OLDPWD"));
		g_code = 126;
	}
	else if (!ft_strcmp(parser->parser_cmd, \
	"/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki"))
		printf("bash: %s: No such file or directory\n", \
				parser->parser_cmd);
	else
	{
		printf("bash: %s: command not found\n", parser->parser_cmd);
		g_code = 127;
	}
	exit(g_code);
}

void	exec_cmd(t_parser *parser, char **cmds, t_env *env)
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
			execve_error(parser, env);
	}
	else
	{
		waitpid(pid, &status, 0);
		g_code = status;
		ft_exit_status(status);
	}
}
