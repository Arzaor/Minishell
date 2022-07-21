/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hterras <hterras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:51:06 by hterras           #+#    #+#             */
/*   Updated: 2022/07/21 17:51:34 by hterras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_i1(char *line, int i, int count, t_parser *parser)
{
	char	letter;

	letter = 0;
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

int	ft_count_i(t_parser *parser, char *line)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (parser->parser_cmd)
		i += ft_strlen(parser->parser_cmd);
	while (line[i] == ' ')
		i++;
	if (parser->parser_opt)
		i = ft_count_i1(line, i, count, parser);
	return (i);
}
