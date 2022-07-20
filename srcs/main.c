/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:18:10 by jbarette          #+#    #+#             */
/*   Updated: 2022/07/20 17:36:50 by jbarette         ###   ########.fr       */
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
		init_signals();
		line = readline(":> ");
		if (line == NULL)
			ft_exit_with_line(line);
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
		{
			printf("\e[2K");
			rl_on_new_line();
			rl_redisplay();
		}
		if (g_code == -111)
		{
			printf("^C");
			printf("\n");
		}
		g_code = 130;
	}
	else if (sig == SIGQUIT)
	{
		if (g_code == -111)
		{
			printf("^\\Quit: 3");
			printf("\n");
		}
		g_code = 131;
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	start_minishell(env);
	return (0);
}
