/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:47:16 by jbarette          #+#    #+#             */
/*   Updated: 2022/08/06 13:07:37 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote_and_count(char *line)
{
	int	i;

	i = 0;
	if (line[0] == '\'' || line[0] == '"')
	{
		i++;
		while (line[i] && line[i] != line[0])
			i++;
		i++;
	}
	else
	{
		while (line[i] && line[i] != ' ')
			i++;
	}
	return (i);
}

t_parser	*parsing_cmd(char *line, t_parser *parser, t_env *env)
{
	int	i;
	int	y;
	int	count;
	int	tmp;

		y = 0;
	count = 0;
	tmp = 0;
	i = check_quote_and_count(line);
	parser->parser_cmd = malloc(sizeof(char) * i + 1);
	while (count < i)
		parser->parser_cmd[y++] = line[count++];
	parser->parser_cmd[y] = '\0';
	tmp = transform_cmd(parser, env);
	if (!parser->parser_error)
		save_to_cmd(parser, env);
	return (parser);
}
