/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hterras <hterras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:18:10 by jbarette          #+#    #+#             */
/*   Updated: 2022/07/06 14:20:23 by hterras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	start_minishell(char **env)
{
	char	*line;
	t_env	*envp;

	envp = create_env(env);
	while (1)
	{
		style_prompt();
		signal(SIGQUIT, sig_handler);
		signal(SIGINT, sig_handler);
		line = readline(":> ");
		if (line == NULL)
			ft_exit_with_line(line);
		if (line && g_code == -110 && ft_strncmp(line,"^\\",ft_strlen(line)))
			ft_exit_with_line2(line);
		if (ft_strlen(line) > 0)
			show_prompt(line, envp);
		free(line);
	}
	free(envp);
}

void	sig_handler2(int sig)
{
	if (sig == SIGINT)
	{
		if (g_code != -111)
			printf("\e[2K");
		if (g_code == -111)
			printf("\n");
		g_code = 130;
	}
	else if (sig == SIGQUIT)
	{
		if (g_code == -111)
		{
			printf("Quit:3");
			printf("\n");
		}
		g_code = 131;
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
	
	start_minishell(env);
	return (0);
}
