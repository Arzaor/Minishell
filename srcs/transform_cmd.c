/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:09:02 by jbarette          #+#    #+#             */
/*   Updated: 2022/08/03 16:36:59 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	transform_cmd1(t_parser *parser, int i)
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

static int	transform_cmd2(t_parser *parser, int i, t_env *env)
{
	if (parser->parser_cmd[i] == '$' && \
			parser->parser_cmd[i + 1] != '?')
		i = get_var_env_cmd(parser, i, env, 1);
	else if (parser->parser_cmd[i] == '$' && \
				parser->parser_cmd[i + 1] == '?')
		i = transform_cmd1(parser, i);
	return (i);
}

static int	transform_cmd3(t_parser *parser, int i)
{
	parser->parser_count++;
	i++;
	return (i);
}

static void	transform_cmd_exit(t_parser *parser)
{
	printf("Erreur : Format quote.\n");
	g_code = 1;
	parser->parser_error = 1;
}

int	transform_cmd(t_parser *parser, t_env *env)
{
	int	i;

	i = 0;
	while (parser->parser_cmd[i])
	{
		if (parser->parser_cmd[i] != '\'' && \
				parser->parser_cmd[i] != '"' && parser->parser_cmd[i] != '$')
			i = transform_cmd3(parser, i);
		else if (parser->parser_cmd[i] == '\'' || \
					parser->parser_cmd[i] == '"')
		{
			i = found_second_quote_cmd(parser, i, parser->parser_cmd[i], env);
			if (i == -1)
			{
				transform_cmd_exit(parser);
				break ;
			}
			if (parser->parser_cmd[i] == '\'' || parser->parser_cmd[i] == '"')
				i += 1;
		}
		else
			i = transform_cmd2(parser, i, env);
	}
	return (1);
}
