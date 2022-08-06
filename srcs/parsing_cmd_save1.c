/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd_save1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:57:56 by jbarette          #+#    #+#             */
/*   Updated: 2022/08/06 13:10:45 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fsq_save_cmd2(t_parser *parser, t_env *env, char quote, int i)
{
	int		k;
	char	*code;

	k = 0;
	code = 0;
	while (parser->parser_cmd[i] != quote)
	{
		if (parser->parser_cmd[i] == '$' && parser->parser_cmd[i + 1] != '?')
			i = get_var_env_cmd(parser, i, env, 0);
		else if (parser->parser_cmd[i] == '$' && \
					parser->parser_cmd[i + 1] == '?')
		{
			if (g_code != 0)
				add_number_in_tab(parser, parser->parser_commands);
			else
				parser->parser_commands[parser->parser_count++] = '0';
			i += 2;
		}
		else
		{
			parser->parser_commands[parser->parser_count++] = \
				parser->parser_cmd[i++];
		}
	}
	return (i);
}

static int	fsq_save_cmd3(t_parser *parser, t_env *env, char quote, int i)
{
	if (quote == '\'')
	{
		while (parser->parser_cmd[i] != quote)
		{
			parser->parser_commands[parser->parser_count++] = \
				parser->parser_cmd[i++];
		}
	}
	else
		i = fsq_save_cmd2(parser, env, quote, i);
	return (i);
}

int	found_second_quote_save_cmd(t_parser *parser, int i, \
				char quote, t_env *env)
{
	int	result;
	int	tmp;

	result = 0;
	if (parser->parser_cmd[i + 1])
		i += 1;
	else
		return (-1);
	tmp = i;
	while (parser->parser_cmd[i])
	{
		if (parser->parser_cmd[i] == quote)
		{
			result = 1;
			break ;
		}
		i++;
	}
	i = tmp;
	if (result)
		i = fsq_save_cmd3(parser, env, quote, i);
	else
		return (-1);
	return (i);
}
