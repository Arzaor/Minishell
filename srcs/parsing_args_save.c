/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args_save.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:51:06 by hterras           #+#    #+#             */
/*   Updated: 2022/08/07 15:14:24 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	transform_arg_save1(t_parser *parser, int i)
{
	int		k;
	char	*code;

	code = 0;
	k = 0;
	if (g_code != 0)
	{
		code = ft_itoa_base(g_code, 10);
		while (code[k])
			parser->parser_arguments[parser->parser_count++] = \
				code[k++];
	}
	else
		parser->parser_arguments[parser->parser_count++] = '0';
	i += 2;
	free(code);
	return (i);
}

static int	transform_arg_save2(t_parser *parser, int i, t_env *env)
{
	if (parser->parser_args[i] == '\'' || \
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
		i = transform_arg_save1(parser, i);
	return (i);
}

static void	transform_arg_save(t_parser *parser, t_env *env)
{
	int	i;

	i = 0;
	while (parser->parser_args[i])
	{
		if (parser->parser_args[i] != '\'' && parser->parser_args[i] \
				!= '"' && parser->parser_args[i] != '$')
		{
			if (ft_isspace(parser->parser_args[i]) && \
				ft_isspace(parser->parser_args[i + 1]))
				i++;
			else
				parser->parser_arguments[parser->parser_count++] = \
				parser->parser_args[i++];
		}
		else
			i = transform_arg_save2(parser, i, env);
	}
	parser->parser_arguments[parser->parser_count] = '\0';
}

void	save_to_arg(t_parser *parser, t_env *env)
{
	parser->parser_arguments = malloc(sizeof(char) * parser->parser_count + 1);
	parser->parser_count = 0;
	transform_arg_save(parser, env);
	free(parser->parser_args);
	parser->parser_args = ft_strdup(parser->parser_arguments);
}
