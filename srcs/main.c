/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hterras <hterras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:18:10 by jbarette          #+#    #+#             */
/*   Updated: 2022/06/27 12:45:55 by hterras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	show_prompt(char *line, t_env *envp)
{
	t_parser	*parser;

	parser = init();
	if (line)
		add_history(line);
	parsing_symbols(parser, line, envp);
}

static void	start_minishell(char **env)
{
	char	*line;
	t_env	*envp;

	envp = create_env(env);
	while (1)
	{
		style_prompt();
		line = readline(":> ");
		if (line == NULL)
			ft_exit_with_line(line);
		if (ft_strlen(line) > 0)
			show_prompt(line, envp);
		free(line);
	}
	free(envp);
}

void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("\e[2K");
		rl_on_new_line();
		rl_redisplay();
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signo == SIGQUIT)
	{
		printf("\e[2K");
		rl_on_new_line();
		rl_redisplay();
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	start_minishell(env);
	return (0);
}
