/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:33:03 by jbarette          #+#    #+#             */
/*   Updated: 2022/06/29 15:44:30 by jbarette         ###   ########.fr       */
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

/*
int	check_quote_redir(char *line, int i)
{
	char	quote;
	int		in_quote;
	int		pos;
	int		second_pos;
	int		i;

	quote = 0;
	in_quote = 0;
	pos = 0;
	second_pos = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			in_quote = 1;
			pos = i;
			quote = line[i];
			break ;
		}
		i++;
	}
	if (in_quote != 0)
	{
		pos += 1;
		while (line[pos])
		{
			if (line[pos] == quote)
			{
				second_pos = pos;
				break ;
			}
			pos++;
		}
	}
	pos = i;
	while (pos < second_pos)
	{
		if (line[pos] == '<' || line[pos] == '>')
			return (1);
		pos++;
	}
	return (0);
}
*/

int	check_quote_redir(char *line, int i)
{
	char	quote;
	int		a;
	int		in_quote;
	int		length;

	quote = 0;
	a = 0;
	in_quote = 0;
	length = ft_strlen(line);
	while (a < i)
	{
		if (line[a] == '\'' || line[a] == '"')
		{
			in_quote = 1;
			quote = line[a];
			break ;
		}
		a++;
	}
	if (in_quote)
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

	k = 0;
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
	}
	return (parser);
}
