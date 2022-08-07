/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:47:16 by jbarette          #+#    #+#             */
/*   Updated: 2022/08/07 15:17:46 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote_and_count(char *line, int count)
{
	int	i;

	i = count;
	if (line[count] == '\'' || line[count] == '"')
	{
		i++;
		while (line[i] && line[i] != line[count])
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

	y = 0;
	count = 0;
	while (line[count] && line[count] == ' ')
		count++;
	i = check_quote_and_count(line, count);
	parser->parser_cmd = malloc(sizeof(char) * i + 1);
	while (count < i)
		parser->parser_cmd[y++] = line[count++];
	parser->parser_cmd[y] = '\0';
	transform_cmd(parser, env);
	if (!parser->parser_error)
		save_to_cmd(parser, env);
	return (parser);
}
