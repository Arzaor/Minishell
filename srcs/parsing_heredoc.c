/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hterras <hterras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:22:17 by hterras           #+#    #+#             */
/*   Updated: 2022/07/18 10:40:26 by hterras          ###   ########.fr       */
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

	i = 1;
	test = NULL;
	if (parser->parser_right_redir == 2 || parser->parser_dright_redir == 4)
		test = ft_split(line, '>');
	else
		test = ft_split(line, '<');
	if (parser->parser_right_redir == 2)
	{
		//i = 0;
		while (test[i])
			open(ft_strtrim(test[i++]), O_CREAT| O_TRUNC | O_RDWR, 0666);
		parser = save_heredoc(parser, i - 1 , test);
	}
	if(parser->parser_dleft_redir != 3)
	{
		while (test[i])
			open(ft_strtrim(test[i++]), O_CREAT | O_RDWR, 0666);
		parser = save_heredoc(parser, i - 1, test);
	}
	else
		parser = save_heredoc(parser, 1, test);
	free_array(test);
	return (parser);
}
