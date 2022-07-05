/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:18:10 by jbarette          #+#    #+#             */
/*   Updated: 2022/07/05 16:11:18 by jbarette         ###   ########.fr       */
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
		if (line && g_code == 138)
			ft_exit_with_line2(line);
		if (ft_strlen(line) > 0)
			show_prompt(line, envp);
		free(line);
	}
	free(envp);
}

void	handler_child(int sig)
{
	if (sig == SIGINT)
	{
		if (g_code != -111)
			printf("\e[2K");
		if (g_code == -111)
			printf("\n");
	}
	else if (sig == SIGQUIT)
	{
		if (g_code == -111)
		{
			printf("Quit:3");
			printf("\n");
		}
	}
}

void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		g_code = 1;
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
		g_code = -110;
		printf("\e[2K");
		rl_on_new_line();
		rl_redisplay();
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	signal(SIGQUIT, sig_handler);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, handler_child);
	signal(SIGINT, handler_child);
	start_minishell(env);
	return (0);
}
