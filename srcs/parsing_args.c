/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:33:03 by jbarette          #+#    #+#             */
/*   Updated: 2022/07/06 14:00:01 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_i(t_parser *parser, char *line)
{
	int	i;

	i = 0;
	if (parser->parser_cmd)
		i += ft_strlen(parser->parser_cmd);
	while (line[i] == ' ')
		i++;
	if (parser->parser_opt)
	{
		if (line[i] == '-')
		{
			i++;
			while (line[i] != ' ')
				i++;
			i += 1;
		}
	}
	return (i);
}

char	send_quote(char *line, int i)
{
	int	a;

	a = 0;
	while (a < i)
	{
		if (line[a] == '\'' || line[a] == '"')
			return (line[a]);
		a++;
	}
	return (0);
}

int	check_quote_redir(char *line, int i)
{
	char	quote;
	int		length;

	length = ft_strlen(line);
	quote = send_quote(line, i);
	if (quote != 0)
	{
		while (i < length)
		{
			if (line[i] == quote)
				return (1);
			i++;
		}
	}
	return (0);
}

t_parser	*parsing_args(char *line, t_parser *parser)
{
	int		i;
	int		k;
	int		count;

	count = 0;
	i = ft_count_i(parser, line);
	k = i;
	while (line[i])
	{
		if ((line[i] == '>' || line[i] == '<') && !check_quote_redir(line, i))
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
		parser->parser_args[k] = '\0';
	}
	return (parser);
}
