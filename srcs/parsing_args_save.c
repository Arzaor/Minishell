/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args_save.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:51:06 by hterras           #+#    #+#             */
/*   Updated: 2022/07/27 16:12:23 by jbarette         ###   ########.fr       */
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

static int	found_second_quote_save(t_parser *parser, int i, \
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

static void	transform_arg_save(t_parser *parser, t_env *env)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (parser->parser_args[i])
	{
		if (parser->parser_args[i] != '\'' && parser->parser_args[i] \
				!= '"' && parser->parser_args[i] != '$')
			parser->parser_arguments[parser->parser_count++] = \
				parser->parser_args[i++];
		else if (parser->parser_args[i] == '\'' || \
				parser->parser_args[i] == '"')
		{
			i = found_second_quote_save(parser, i, parser->parser_args[i], env);
			if (parser->parser_args[i] == '\'' || \
					parser->parser_args[i] == '"')
				i += 1;
		}
		else if (parser->parser_args[i] == '$' && \
				parser->parser_args[i + 1] != '?')
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
	}
	parser->parser_arguments[parser->parser_count] = '\0';
}

void	save_to_arg(t_parser *parser, t_env *env)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	parser->parser_arguments = malloc(sizeof(char) * parser->parser_count + 1);
	parser->parser_count = 0;
	transform_arg_save(parser, env);
	free(parser->parser_args);
	parser->parser_args = malloc(sizeof(char) * parser->parser_count + 1);
	while (parser->parser_arguments[i])
		parser->parser_args[k++] = parser->parser_arguments[i++];
	parser->parser_args[k] = '\0';
}
