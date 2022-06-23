/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hterras <hterras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:47:29 by hterras           #+#    #+#             */
/*   Updated: 2022/06/23 15:56:10 by hterras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_build_in(char *cmd)
{
	const char	*built_in[7];
	int			i;

	i = 0;
	built_in[0] = "echo";
	built_in[1] = "cd";
	built_in[2] = "pwd";
	built_in[3] = "export";
	built_in[4] = "unset";
	built_in[5] = "env";
	built_in[6] = NULL;
	while (built_in[i])
	{
		if (!ft_strcmp(built_in[i], cmd))
			return (true);
		i++;
	}
	return (false);
}

void	get_absolute_path(char *path, t_parser *parser)
{
	char	**path_split;
	int		i;
	char	*bin;

	i = 0;
	path_split = ft_split(path, ':');
	free (path);
	while (path_split[i])
	{
		bin = ft_calloc(sizeof(char), \
			(strlen(path_split[i]) + 1 + strlen(parser->parser_cmd) + 1));
		if (bin == NULL)
			break ;
		strcat(bin, path_split[i]);
		strcat(bin, "/");
		strcat(bin, parser->parser_cmd);
		if (access(bin, F_OK) == 0)
			break ;
		free(bin);
		bin = NULL;
		i++;
	}
	free_array(path_split);
	if (bin)
		parser->parser_cmd = bin;
}

void	exec_cmd(t_parser *parser, char **cmds)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
		printf("Fork");
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		if (execve(parser->parser_cmd, cmds, NULL) == -1)
			printf("bash: %s: command not found\n", cmds[0]);
		exit(0);
	}
}

void	create_cmd(t_parser *parser, t_env *env)
{
	if (!ft_strncmp(parser->parser_cmd, "echo", 4))
		ft_echo(parser, env);
	if (!ft_strncmp(parser->parser_cmd, "cd", 2))
		ft_cd(parser);
	if (!ft_strncmp(parser->parser_cmd, "pwd", 3))
		pwd();
	if (!ft_strncmp(parser->parser_cmd, "export", 6))
		ft_export(env, parser->parser_args);
	if (!ft_strncmp(parser->parser_cmd, "unset", 5))
		ft_unset(env, parser->parser_args);
	if (!ft_strncmp(parser->parser_cmd, "env", 3))
		ft_env(env);
}

void	handler_cmd(t_parser *parser, t_env *env, char **cmds)
{
	if (!is_build_in(parser->parser_cmd) && \
		cmds[0][0] != '/' && ft_strncmp(cmds[0], "./", 2) != 0)
		get_absolute_path(get_env(env, "PATH"), parser);
	handler_redir(parser, cmds, env);
}
