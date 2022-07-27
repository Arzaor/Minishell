/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args_save1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:57:56 by jbarette          #+#    #+#             */
/*   Updated: 2022/07/27 16:59:33 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fsq2(t_parser *parser, t_env *env, char quote, int i)
{
	int	k;

	k = 0;
	while (parser->parser_args[i] != quote)
	{
		if (parser->parser_args[i] == '$' && parser->parser_args[i + 1] != '?')
			i = get_var_env(parser, i, env, 0);
		else if (parser->parser_args[i] == '$' && \
					parser->parser_args[i + 1] == '?')
		{
			if (g_code != 0)
			{
				while (ft_itoa_base(g_code, 10)[k])
					parser->parser_arguments[parser->parser_count++] = \
							ft_itoa_base(g_code, 10)[k++];
			}
			else
				parser->parser_arguments[parser->parser_count++] = '0';
			i += 2;
		}
		else
			parser->parser_arguments[parser->parser_count++] = \
					parser->parser_args[i++];
	}
	return (i);
}

static int	fsq3(t_parser *parser, t_env *env, char quote, int i)
{
	if (quote == '\'')
	{
		while (parser->parser_args[i] != quote)
			parser->parser_arguments[parser->parser_count++] = \
				parser->parser_args[i++];
	}
	else
		i = fsq2(parser, env, quote, i);
	return (i);
}

int	found_second_quote_save(t_parser *parser, int i, \
				char quote, t_env *env)
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
		i = fsq3(parser, env, quote, i);
	else
		return (-1);
	return (i);
}
