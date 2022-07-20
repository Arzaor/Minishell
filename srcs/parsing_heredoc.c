/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:22:17 by hterras           #+#    #+#             */
/*   Updated: 2022/07/20 18:53:32 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser	*save_heredoc(t_parser *parser, int i, char **test)
{
	int	k;
	int	j;

	k = 0;
	j = 0;
	parser->parser_heredoc = malloc(sizeof(char) * \
							ft_strlen(ft_strtrim(test[i])));
	while (test[i][j])
		parser->parser_heredoc[k++] = test[i][j++];
	parser->parser_heredoc[k] = '\0';
	return (parser);
}

t_parser	*parsing_heredoc(char *line, t_parser *parser)
{
	int		i;
	char	**test;
	int		fd;

	i = 1;
	test = NULL;
	fd = -1;
	if (parser->parser_right_redir == 2 || parser->parser_dright_redir == 4)
		test = ft_split(line, '>');
	else
		test = ft_split(line, '<');
	while (test[i])
	{
		if (parser->parser_right_redir == 2)
			fd = open(ft_strtrim(test[i]), O_CREAT | O_TRUNC | O_RDWR, 0666);
		else if (parser->parser_dleft_redir != 3)
			fd = open(ft_strtrim(test[i]), O_CREAT | O_RDWR, 0666);
		i++;
		close (fd);
	}
	parser = save_heredoc(parser, i - 1, test);
	free_array(test);
	return (parser);
}
