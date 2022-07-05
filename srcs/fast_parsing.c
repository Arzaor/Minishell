/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fast_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:46:23 by jbarette          #+#    #+#             */
/*   Updated: 2022/07/05 16:48:12 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**fast_parsing(t_parser *parser, char *line)
{
	char	**cmds;
	char	**cmds_bis;

	cmds = NULL;
	cmds_bis = NULL;
	if (parser->parser_left_redir != 0 \
		|| parser->parser_dleft_redir != 0)
	{
		cmds = ft_split(line, '<');
		cmds_bis = ft_split(cmds[0], ' ');
		free_array(cmds);
	}
	else if (parser->parser_right_redir != 0 \
			|| parser->parser_dright_redir != 0)
	{
		cmds = ft_split(line, '>');
		cmds_bis = ft_split(cmds[0], ' ');
		free_array(cmds);
	}
	else
		cmds_bis = ft_split(line, ' ');
	return (cmds_bis);
}
