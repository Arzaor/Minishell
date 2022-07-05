/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:22:17 by hterras           #+#    #+#             */
/*   Updated: 2022/07/05 17:46:37 by jbarette         ###   ########.fr       */
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

/*
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
*/

t_parser	*parsing_heredoc(char *line, t_parser *parser)
{
	int		i;
	int		j;
	int		k;
	int		count;
	char	**test;

	i = 1;
	j = 0;
	k = 0;
	count = 0;
	if (parser->parser_right_redir == 2 || parser->parser_dright_redir == 4)
		test = ft_split(line, '>');
	else
		test = ft_split(line, '<');
	while (test[i])
		open(ft_strtrim(test[i++]), O_CREAT | O_RDWR, 0666);
	parser->parser_heredoc = malloc(sizeof(char) * \
							ft_strlen(ft_strtrim(test[i - 1])));
	while (test[i - 1][j])
		parser->parser_heredoc[k++] = test[i - 1][j++];
	parser->parser_heredoc[k] = '\0';
	free_array(test);
	return (parser);
}
