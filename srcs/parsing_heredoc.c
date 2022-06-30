/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:22:17 by hterras           #+#    #+#             */
/*   Updated: 2022/06/30 13:02:18 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser	*save_heredoc(t_parser *parser, int count, int i, char *line)
{
	int		k;

	k = 0;
	if (count > 0)
	{
		parser->parser_heredoc = malloc(sizeof(char) * count + 1);
		while (line[i] && line[i] != ' ')
		{
			parser->parser_heredoc[k++] = line[i];
			i++;
		}
		parser->parser_heredoc[k] = '\0';
	}
	return (parser);
}

static int	ft_handler_space(char *line, t_parser *parser, int i)
{
	if ((line[i] == '>' && ft_isalpha(line[i + 1])) || \
		(line[i] == '<' && ft_isalpha(line[i + 1])))
		i += 1;
	else if ((line[i] == '>' && line[i + 1] == ' ' ) || \
		(line[i] == '<' && line[i + 1] == ' '))
		i += 2;
	else if ((line[i] == '>' && line[i + 1] == '>' && \
		ft_isalpha(line[i + 2])) || \
		(line[i] == '<' && line[i + 1] == '<' && ft_isalpha(line[i + 2])))
		i += 2;
	else if ((line[i + 1] == '>' && line[i + 2] == ' ') || \
		(line[i + 1] == '<' && line[i + 2] == ' '))
		i += 3;
	else
	{
		g_code = 258;
		printf("bash: syntax error near unexpected token `newline'\n");
		parser->parser_heredoc = NULL;
		return (-1);
	}
	return (i);
}

t_parser	*parsing_heredoc(char *line, t_parser *parser)
{
	int		i;
	int		k;
	int		count;

	i = 0;
	k = 0;
	count = 0;
	if (parser->parser_right_redir == 2 || parser->parser_left_redir == 1 || \
		parser->parser_dright_redir == 4 || parser->parser_dleft_redir == 3)
	{
		while (line[i])
		{
			if ((line[i] == '>' || line[i] == '<') && !(check_quote_redir(line, i)))
				break ;
			i++;
		}
		i = ft_handler_space(line, parser, i);
		if (i > 0)
		{
			k = i;
			while (line[i] && line[i] != ' ')
			{
				count++;
				i++;
			}
			parser = save_heredoc(parser, count, k, line);
		}
	}
	return (parser);
}
