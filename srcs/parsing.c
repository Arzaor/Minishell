/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:37:10 by jbarette          #+#    #+#             */
/*   Updated: 2022/07/29 23:22:41 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_parser	*parsing(t_parser *parser, char *line, t_env *env)
{
	parser = parsing_cmd(line, parser);
	if (!strcmp(parser->parser_cmd, "cat") || \
		!strcmp(parser->parser_cmd, "sort"))
	{
		g_code = -111;
	}
	parser = parsing_opts(line, parser);
	parser = parsing_args(line, parser, env);
	return (parser);
}

t_parser	*parsing_opts(char *line, t_parser *parser)
{
	int		i;
	int		j;

	i = ft_strlen(parser->parser_cmd);
	i += 1;
	j = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		if (line[i] == '-')
		{
			i += 1;
			j = i;
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