/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:33:03 by jbarette          #+#    #+#             */
/*   Updated: 2022/06/23 16:34:27 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_i(t_parser *parser, char *line)
{
	int	i;

	i = 0;
	if (parser->parser_cmd)
		i += ft_strlen(parser->parser_cmd);
	if (line[i] == ' ')
		i++;
	if (parser->parser_opt)
		i += 3;
	return (i);
}

t_parser	*parsing_args(char *line, t_parser *parser)
{
	int		i;
	int		k;
	int		count;

	k = 0;
	count = 0;
	i = ft_count_i(parser, line);
	k = i;
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '<')
			break ;
		count++;
		i++;
	}
	i = k;
	k = 0;
	if (count > 0)
	{
		parser->parser_args = malloc(sizeof(char) * count + 1);
		while (k < count)
			parser->parser_args[k++] = line[i++];
	}
	return (parser);
}
