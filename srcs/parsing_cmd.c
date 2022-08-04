/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hterras <hterras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:47:16 by jbarette          #+#    #+#             */
/*   Updated: 2022/08/04 16:00:37 by hterras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser	*parsing_cmd(char *line, t_parser *parser, t_env *env)
{
	int	i;
	int	y;
	int	count;
	int	tmp;

	i = 0;
	y = 0;
	count = 0;
	tmp = 0;
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
	parser->parser_cmd = malloc(sizeof(char) * i + 1);
	while (count < i)
		parser->parser_cmd[y++] = line[count++];
	parser->parser_cmd[y] = '\0';
	tmp = transform_cmd(parser, env);
	if (!parser->parser_error)
		save_to_cmd(parser, env);
	return (parser);
}
