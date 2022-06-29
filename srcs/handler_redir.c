/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:37:44 by hterras           #+#    #+#             */
/*   Updated: 2022/06/29 16:26:34 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_redir(t_parser *parser, char **cmds, t_env *env)
{
	int		saveout1;
	int		i;

	saveout1 = 0;
	i = 0;
	
	if (parser->parser_left_redir == 1)
		saveout1 = handler_left_redir(parser, parser->parser_heredoc);
	if (parser->parser_right_redir == 2)
		saveout1 = handler_right_redir(parser);
	if (parser->parser_dleft_redir == 3)
		saveout1 = handler_dleft_redir(parser);
	if (parser->parser_dright_redir == 4)
		saveout1 = handler_dright_redir(parser);
	if (is_build_in(parser->parser_cmd))
		create_cmd(parser, env);
	else
		exec_cmd(parser, cmds);
	clean_redir(parser, saveout1);
}

void	clean_redir(t_parser *parser, int saveout1)
{
	if (parser->parser_left_redir == 1)
		dup2(saveout1, 0);
	if (parser->parser_right_redir == 2)
		dup2(saveout1, 1);
	if (parser->parser_dleft_redir == 3 && \
			!ft_strcmp(parser->parser_cmd, "/bin/cat"))
		dup2(saveout1, 0);
	if (parser->parser_dright_redir == 4)
		dup2(saveout1, 1);
}
