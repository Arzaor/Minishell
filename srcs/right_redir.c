/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hterras <hterras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:42:02 by hterras           #+#    #+#             */
/*   Updated: 2022/06/23 17:08:42 by hterras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handler_dright_redir(t_parser *parser)
{
	int		saveout1;

	saveout1 = dup(1);
	close(1);
	dup2(open(parser->parser_heredoc, O_CREAT | O_RDWR | O_APPEND, 0666), 1);
	return (saveout1);
}

int	handler_right_redir(t_parser *parser)
{
	int		saveout1;
	int		fd;

	fd = open(parser->parser_heredoc, O_RDWR);
	saveout1 = dup(1);
	close(1);
	if (fd == -1)
		dup2(open(parser->parser_heredoc, O_CREAT| O_TRUNC | O_RDWR, 0666), 1);
	else
		dup2(open(parser->parser_heredoc, O_TRUNC | O_RDWR, 0666), 1);
	return (saveout1);
}
