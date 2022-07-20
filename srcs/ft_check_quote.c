/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:16:56 by jbarette          #+#    #+#             */
/*   Updated: 2022/07/21 01:53:45 by jbarette         ###   ########.fr       */
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

int	ft_check_quote(t_parser *parser, int i, char quote, t_env *env)
{
	int		s;
	int		in_quote;

	s = 0;
	in_quote = 0;
	s = i;
	if (ft_strlen(parser->parser_args) <= 1 && parser->parser_args[i] == quote)
	{
		format_quotes();
		return (i);
	}
	while (parser->parser_args[++i])
	{
		if (parser->parser_args[i] == quote)
		{
			in_quote = 1;
			break ;
		}
	}
	if (in_quote)
		while (s < i)
			s = ft_append_value(parser, s, quote, env);
	else if (parser->parser_args[i + 1] != quote)
		format_quotes();
	return (i);
}
