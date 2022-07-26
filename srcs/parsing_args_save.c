/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args_save.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:51:06 by hterras           #+#    #+#             */
/*   Updated: 2022/07/26 14:28:53 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_var_env_save(t_parser *parser, int i, t_env *env)
{
	char	*var_env;
	char	*env_def;
	int		length;
	int		tmp;
	int		k;

	var_env = 0;
	env_def = 0;
	i += 1;
	tmp = i;
	k = 0;
	length = 0;
	while (parser->parser_args[i] && (parser->parser_args[i] >= 'A' && parser->parser_args[i] <= 'Z'))
	{
		length++;
		i++;
	}
	var_env = malloc(sizeof(char) * length + 1);
	i = tmp;
	while (parser->parser_args[i] && (parser->parser_args[i] >= 'A' && parser->parser_args[i] <= 'Z'))
		var_env[k++] = parser->parser_args[i++];
	var_env[k] = '\0';
	env_def = get_env(env, var_env);
	k = 0;
	if (env_def)
	{
		while (env_def[k])
			parser->parser_arguments[parser->parser_count++] = env_def[k++];
	}
	free(env_def);
	free(var_env);
	return (i);
}

static int		found_second_quote_save(t_parser *parser, int i, char quote, t_env *env)
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
	{
		if (quote == '\'')
		{
			while (parser->parser_args[i] != quote)
				parser->parser_arguments[parser->parser_count++] = parser->parser_args[i++];
		}
		else
		{
			while (parser->parser_args[i] != quote)
			{
				if (parser->parser_args[i] == '$' && parser->parser_args[i + 1] != '?')
					i = get_var_env_save(parser, i, env);
				else
					parser->parser_arguments[parser->parser_count++] = parser->parser_args[i++];
			}
		}
	}
	else
		return (-1);
	return (i);
}

static void	transform_arg_save(t_parser *parser, t_env *env)
{
	int	i;

	i = 0;
	while (parser->parser_args[i])
	{
		if (parser->parser_args[i] != '\'' && parser->parser_args[i] != '"' && parser->parser_args[i] != '$')
			parser->parser_arguments[parser->parser_count++] = parser->parser_args[i++];
		else if (parser->parser_args[i] == '\'' || parser->parser_args[i] == '"')
		{
			i = found_second_quote_save(parser, i, parser->parser_args[i], env);
			if (parser->parser_args[i] == '\'' || parser->parser_args[i] == '"')
				i += 1;
		}
		else if (parser->parser_args[i] == '$' && parser->parser_args[i + 1] != '?')
		{
			i = get_var_env_save(parser, i, env);
			if (parser->parser_args[i] == '$')
				i -= 1;
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
