/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:16:56 by jbarette          #+#    #+#             */
/*   Updated: 2022/07/26 15:47:35 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	format_quotes(void)
{
	int		line_count;
	int		col_cocunt;
	char	*cm_cap;

	printf("\e[2K");
	line_count = tgetnum("li");
	col_cocunt = tgetnum("cl");
	cm_cap = tgetstr("cm", NULL);
	tputs(tgoto(cm_cap, col_cocunt, line_count - 1), 1, putchar);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_code = 258;
	printf("Format quotes.");
}