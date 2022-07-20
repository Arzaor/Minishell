/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:52:59 by hterras           #+#    #+#             */
/*   Updated: 2022/07/21 01:53:21 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show_prompt(char *line, t_env *envp)
{
	t_parser	*parser;

	parser = init();
	if (line)
		add_history(line);
	parsing_symbols(parser, line, envp);
}

void	style_prompt(void)
{
	int		ret;
	char	*term_type;
	char	*color_cap;
	char	*reset_cmd;

	term_type = getenv("TERM");
	ret = tgetent(NULL, term_type);
	color_cap = tgetstr("AF", NULL);
	tputs(tparm(color_cap, COLOR_GREEN), 1, putchar);
	reset_cmd = tgetstr("md", NULL);
	tputs(reset_cmd, 1, putchar);
}

char	send_quote(char *line, int i)
{
	int	a;

	a = 0;
	while (a < i)
	{
		if (line[a] == '\'' || line[a] == '"')
			return (line[a]);
		a++;
	}
	return (0);
}

int	check_quote_redir(char *line, int i)
{
	char	quote;
	int		length;

	length = ft_strlen(line);
	quote = send_quote(line, i);
	if (quote != 0)
	{
		while (i < length)
		{
			if (line[i] == quote)
				return (1);
			i++;
		}
	}
	return (0);
}
