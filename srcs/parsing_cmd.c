/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:47:16 by jbarette          #+#    #+#             */
/*   Updated: 2022/06/23 16:47:26 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser	*parsing_cmd(char *line, t_parser *parser)
{
	int	i;
	int	y;
	int	count;

	i = 0;
	y = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			break ;
		if (line[i] == '>' || line[i] == '<')
			break ;
		i++;
	}
	parser->parser_cmd = malloc(sizeof(char) * i + 1);
	while (count < i)
		parser->parser_cmd[y++] = line[count++];
	parser->parser_cmd[y] = '\0';
	return (parser);
}