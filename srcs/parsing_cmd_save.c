/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd_save.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:51:06 by hterras           #+#    #+#             */
/*   Updated: 2022/08/03 16:43:37 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	transform_cmd_save1(t_parser *parser, int i)
{
	int		k;
	char	*code;

	code = 0;
	k = 0;
	if (g_code != 0)
	{
		code = ft_itoa_base(g_code, 10);
		while (code[k])
			parser->parser_commands[parser->parser_count++] = \
				code[k++];
	}
	else
		parser->parser_commands[parser->parser_count++] = '0';
	i += 2;
	free(code);
	return (i);
}

static int	transform_cmd_save2(t_parser *parser, int i, t_env *env)
{
	if (parser->parser_cmd[i] == '\'' || \
			parser->parser_cmd[i] == '"')
	{
		i = found_second_quote_save_cmd(parser, i, parser->parser_cmd[i], env);
		if (parser->parser_cmd[i] == '\'' || \
				parser->parser_cmd[i] == '"')
			i += 1;
	}
	else if (parser->parser_cmd[i] == '$' && \
			parser->parser_cmd[i + 1] != '?')
		i = get_var_env_cmd(parser, i, env, 0);
	else if (parser->parser_cmd[i] == '$' && \
			parser->parser_cmd[i + 1] == '?')
		i = transform_cmd_save1(parser, i);
	return (i);
}

static void	transform_cmd_save(t_parser *parser, t_env *env)
{
	int	i;

	i = 0;
	while (parser->parser_cmd[i])
	{
		if (parser->parser_cmd[i] != '\'' && parser->parser_cmd[i] \
				!= '"' && parser->parser_cmd[i] != '$')
		{
			if (ft_isspace(parser->parser_cmd[i]) && \
				ft_isspace(parser->parser_cmd[i + 1]))
				i++;
			else
				parser->parser_commands[parser->parser_count++] = \
				parser->parser_cmd[i++];
		}
		else
			i = transform_cmd_save2(parser, i, env);
	}
	parser->parser_commands[parser->parser_count] = '\0';
}

void	save_to_cmd(t_parser *parser, t_env *env)
{
	parser->parser_commands = malloc(sizeof(char) * parser->parser_count + 1);
	parser->parser_count = 0;
	transform_cmd_save(parser, env);
	free(parser->parser_cmd);
	parser->parser_cmd = ft_strdup(parser->parser_commands);
	parser->parser_count = 0;
}
