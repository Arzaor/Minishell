/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hterras <hterras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:09:44 by jbarette          #+#    #+#             */
/*   Updated: 2022/06/27 14:37:23 by hterras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_append_value(t_parser *parser, int s, char quote, t_env *env)
{
	if (parser->parser_args[s] == '$' && quote == '"')
		s = check_dollars(parser, s, env);
	if (parser->parser_args[s] == quote)
	{
		if(quote == '\'')
			parser->parser_single_quote -=1;
		if(quote == '"')
			parser->parser_double_quote -=1;
		s++;
	}
	else
		printf("%c", parser->parser_args[s++]);
	return (s);
}

static int	ft_check_quote(t_parser *parser, int i, char quote, t_env *env)
{
	int		s;
	int		in_quote;

	s = 0;
	in_quote = 0;
	s = i;
	if (ft_strlen(parser->parser_args) <= 1 && parser->parser_args[i] == quote)
	{
		printf("Format quotes.");
		return (i);
	}
	while (parser->parser_args[++i])
	{
		if (parser->parser_args[i] == quote)
		{
			if(quote == '\'')
				parser->parser_single_quote -=1;
			if(quote == '"')
				parser->parser_double_quote -=1;
			in_quote = 1;
			break ;
		}
	}
	if (in_quote)
		while (s < i)
			s = ft_append_value(parser, s, quote, env);

	else if (parser->parser_args[i + 1] != quote)
		printf("Format quotes.");
	return (i);
}

int	ft_show_code(t_parser *parser, int i)
{
	i += 1;
	printf("%d", g_code);
	return (i);
}

void	ft_echo(t_parser *parser, t_env *env)
{
	int		i;
	char	*arg;

	i = 0;
	arg = parser->parser_args;
	if (arg)
	{
		while (arg[i])
		{
			if (arg[i] != '"' && arg[i] != '\'' && arg[i] != '$')
				printf("%c", arg[i]);
			else if (arg[i] == '$' && arg[i + 1] == '?')
				i = ft_show_code(parser, i);
			else if (arg[i] == '"' || arg[i] == '\'')
				i = ft_check_quote(parser, i, arg[i], env);
			else if (arg[i] == '$' && arg[i + 1] != '?')
				i = check_dollars(parser, i, env);
			i++;
		}
		if (!parser->parser_opt)
			printf("\n");
	}
	else
		printf("\n");
}
