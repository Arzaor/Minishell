/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_cursor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:11:12 by jbarette          #+#    #+#             */
/*   Updated: 2022/08/06 13:07:10 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_option(char *line, int i)
{
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i] == '-')
		{
			i++;
			while (line[i] && ft_isalnum(line[i]))
				i++;
		}
		else
			break ;
	}
	while (line[i] && line[i] == ' ')
		i++;
	return (i);
}

static int	count_option_echo1(char *line, int i, char letter, int count)
{
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
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
				i -= count + 1;
				break ;
			}
		}
		else
			break ;
	}
	return (i);
}

int	count_option_echo(char *line, int i)
{
	char	letter;
	int		count;

	letter = 0;
	count = 0;
	i = count_option_echo1(line, i, letter, count);
	if (line[i] == ' ')
		i++;
	return (i);
}

int	count_cursor(t_parser *parser, char *line)
{
	int		i;

	i = 0;
	if (parser->parser_cmd)
		i = check_quote_and_count(line);
	while (line[i] && line[i] == ' ')
		i++;
	if (!ft_strncmp(parser->parser_cmd, "echo", 4))
		i = count_option_echo(line, i);
	else
		i = count_option(line, i);
	return (i);
}
