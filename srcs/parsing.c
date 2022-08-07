/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:37:10 by jbarette          #+#    #+#             */
/*   Updated: 2022/08/06 14:10:44 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_parser	*parsing(t_parser *parser, char *line, t_env *env)
{
	parser = parsing_cmd(line, parser, env);
	if (!is_build_in(parser->parser_cmd))
	{
		g_code = -111;
	}
	parser = parsing_opts(line, parser);
	parser = parsing_args(line, parser, env);
	return (parser);
}

static t_parser	*check_letter_opt(char *line, int j, t_parser *parser)
{
	while (line[j] != ' ')
	{
		if (line[j] != 'n')
		{
			parser->parser_opt = 0;
			break ;
		}
		else
			parser->parser_opt = 1;
		j++;
	}
	return (parser);
}

t_parser	*parsing_opts(char *line, t_parser *parser)
{
	int		i;

	i = ft_strlen(parser->parser_cmd);
	i += 1;
	while (line[i])
	{
		if (parser->parser_opt)
			break ;
		if (line[i] == ' ')
			i++;
		if (line[i] == '-')
		{
			i += 1;
			parser = check_letter_opt(line, i, parser);
		}
		i++;
	}
	return (parser);
}

void	parsing_handler(t_parser *parser, char *line, \
						t_env *env)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			count++;
		i++;
	}
	if (count != ft_strlen(line))
		handler_cmd(parsing(parser, line, env), env, line);
	free_parser(parser);
}
