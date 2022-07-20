/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 13:42:50 by jbarette          #+#    #+#             */
/*   Updated: 2022/07/20 17:08:36 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	echo_off(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		printf("OK");
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, 0, &term) == -1)
		printf("OK");
}

static void	handle_signal(int signal)
{
	g_code = signal + 128;
	if (signal == SIGINT)
	{
		g_code = 1;
		rl_on_new_line();
		rl_redisplay();
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signal == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
}

void	init_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle_signal;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		printf("OK");
	signal(SIGQUIT, SIG_IGN);
	if (isatty(STDIN_FILENO))
		echo_off();
}
