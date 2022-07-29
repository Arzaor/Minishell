/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:44:55 by jbarette          #+#    #+#             */
/*   Updated: 2022/07/29 20:12:37 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_option(char *line, int i, t_parser *parser)
{
	while (line[i])
	{
		if (line[i] == '-')
		{
			i++;
			while (line[i] && ft_isalnum(line[i]))
				i++;
		}
		else
			break ;
		i++;
	}
	while (line[i] && line[i] == ' ')
		i++;
	return (i);
}

int	count_cursor(t_parser *parser, char *line)
{
	int		i;

	i = 0;
	if (parser->parser_cmd)
		i += ft_strlen(parser->parser_cmd);
	while (line[i] && line[i] == ' ')
		i++;
	i = count_option(line, i, parser);
	return (i);
}

static int	fsq2(char quote, t_parser *parser, int i, t_env *env)
{
	while (parser->parser_args[i] != quote)
	{
		if (parser->parser_args[i] == '$' && parser->parser_args[i + 1] != '?')
			i = get_var_env(parser, i, env, 1);
		else if (parser->parser_args[i] == '$' && \
				parser->parser_args[i + 1] == '?')
		{
			if (ft_strlen(ft_itoa_base(g_code, 10)) > 0)
				parser->parser_count += ft_strlen(ft_itoa_base(g_code, 10));
			else
				parser->parser_count++;
			i += 2;
		}
		else
		{
			parser->parser_count++;
			i++;
		}
	}
	return (i);
}

static int	fsq3(char quote, t_parser *parser, int i, t_env *env)
{
	if (quote == '\'')
	{
		while (parser->parser_args[i] != quote)
		{
			parser->parser_count++;
			i++;
		}
	}
	else
		i = fsq2(quote, parser, i, env);
	return (i);
}

int	found_second_quote(t_parser *parser, int i, char quote, t_env *env)
{
	int	result;
	int	tmp;

	result = 0;
	if (parser->parser_args[i + 1])
		i += 1;
	else
		return (-1);
	tmp = i;
	while (parser->parser_args[i])
	{
		if (parser->parser_args[i] == quote)
		{
			result = 1;
			break ;
		}
		i++;
	}
	i = tmp;
	if (result)
		i = fsq3(quote, parser, i, env);
	else
		return (-1);
	return (i);
}
