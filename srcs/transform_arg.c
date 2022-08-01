/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:09:02 by jbarette          #+#    #+#             */
/*   Updated: 2022/08/01 12:13:06 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	transform_arg1(t_parser *parser, int i)
{
	char	*code;

	code = ft_itoa_base(g_code, 10);
	if (ft_strlen(code) > 0)
		parser->parser_count += ft_strlen(code);
	else
		parser->parser_count++;
	i += 2;
	free(code);
	return (i);
}

static int	transform_arg2(t_parser *parser, int i, t_env *env)
{
	if (parser->parser_args[i] == '$' && \
			parser->parser_args[i + 1] != '?')
		i = get_var_env(parser, i, env, 1);
	else if (parser->parser_args[i] == '$' && \
				parser->parser_args[i + 1] == '?')
		i = transform_arg1(parser, i);
	return (i);
}

static int	transform_arg3(t_parser *parser, int i)
{
	parser->parser_count++;
	i++;
	return (i);
}

static void	transform_arg_exit(t_parser *parser)
{
	printf("Erreur : Format quote.\n");
	g_code = 1;
	parser->parser_error = 1;
}

int	transform_arg(t_parser *parser, t_env *env)
{
	int	i;

	i = 0;
	while (parser->parser_args[i])
	{
		if (parser->parser_args[i] != '\'' && \
				parser->parser_args[i] != '"' && parser->parser_args[i] != '$')
			i = transform_arg3(parser, i);
		else if (parser->parser_args[i] == '\'' || \
					parser->parser_args[i] == '"')
		{
			i = found_second_quote(parser, i, parser->parser_args[i], env);
			if (i == -1)
			{
				transform_arg_exit(parser);
				break ;
			}
			if (parser->parser_args[i] == '\'' || parser->parser_args[i] == '"')
				i += 1;
		}
		else
			i = transform_arg2(parser, i, env);
	}
	return (1);
}
