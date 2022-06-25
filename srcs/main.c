/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hterras <hterras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:18:10 by jbarette          #+#    #+#             */
/*   Updated: 2022/06/25 12:57:06 by hterras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exit(void)
{
	int		line_count;
	int		col_cocunt;
	char	*cm_cap;

	line_count = tgetnum("li");
	col_cocunt = tgetnum("cl");
	cm_cap = tgetstr("cm", NULL);
	tputs(
		tgoto(cm_cap, col_cocunt + 4, line_count - 2), 1, putchar
		);
	printf("exit");
}

static void	show_prompt(char *line, t_env *envp)
{
	t_parser	*parser;

	parser = init();
	if (line)
		add_history(line);
	parsing_symbols(parser, line, envp);
	free(line);
}

static void	start_minishell(char **env)
{
	char	*line;
	t_env	*envp;
	int		i = 0;
	envp = create_env(env);
	while (1)
	{
		style_prompt();
		line = readline(":> ");
		if (line == NULL)
		{
			ft_exit();
			break ;
		}
		if (ft_strlen(line) > 0)
		{
			if (ft_strcmp(line, "exit") == 0)
			{
				ft_exit();
				break ;
			}
			else
				show_prompt(line, envp);
				
		}
	}
	free(envp);
}

static void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signo == SIGQUIT)
	{
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
