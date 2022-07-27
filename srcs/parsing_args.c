/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:33:03 by jbarette          #+#    #+#             */
/*   Updated: 2022/07/27 18:02:27 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_option(char *line, int i, t_parser *parser)
{
	char	letter;
	int		count;

	letter = 0;
	count = 0;
	if (line[i] == '-')
	{
		i++;
		while (line[i] == 'n')
		{
			i++;
			count++;
			letter = line[i];
		}
		if (letter != 'n' && letter != ' ')
		{
			i -= count + 2;
			parser->parser_opt = 0;
		}
		i += 1;
	}
	return (i);
}

static int	count_cursor(t_parser *parser, char *line)
{
	int		i;

	i = 0;
	if (parser->parser_cmd)
		i += ft_strlen(parser->parser_cmd);
	while (line[i] == ' ')
		i++;
	if (parser->parser_opt)
		i = count_option(line, i, parser);
	return (i);
}

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

static int	transform_arg(t_parser *parser, t_env *env)
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
				printf("Erreur : Format quote.");
				return (0);
			}
			if (parser->parser_args[i] == '\'' || parser->parser_args[i] == '"')
				i += 1;
		}
		else
			i = transform_arg2(parser, i, env);
	}
	return (1);
}

t_parser	*parsing_args(char *line, t_parser *parser, t_env *env)
{
	int	start;
	int	tmp;
	int	i;

	start = count_cursor(parser, line);
	tmp = start;
	i = 0;
	if (line[start])
	{
		while (line[start])
			start++;
		parser->parser_args = malloc(sizeof(char) * start - tmp + 1);
		start = tmp;
		while (line[start])
			parser->parser_args[i++] = line[start++];
		parser->parser_args[i] = '\0';
		tmp = transform_arg(parser, env);
		if (tmp)
			save_to_arg(parser, env);
		else
			parser->parser_args = NULL;
	}
	else
		parser->parser_args = NULL;
	return (parser);
}
