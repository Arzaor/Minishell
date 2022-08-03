/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:47:16 by jbarette          #+#    #+#             */
/*   Updated: 2022/08/03 17:19:04 by jbarette         ###   ########.fr       */
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
	while (line[i])
	{
		if (line[i] == ' ')
			break ;
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
