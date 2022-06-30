/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:37:10 by jbarette          #+#    #+#             */
/*   Updated: 2022/06/30 12:38:24 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_parser	*parsing(t_parser *parser, char *line)
{
	parser = parsing_cmd(line, parser);
	parser = parsing_opts(line, parser);
	parser = parsing_args(line, parser);
	parser = parsing_heredoc(line, parser);
	return (parser);
}

t_parser	*parsing_opts(char *line, t_parser *parser)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '-' && line[i + 1] == 'n')
			parser->parser_opt = 1;
		i++;
	}
	return (parser);
}

void	parsing_redirection(char *line, t_parser *parser, int i)
{
	if (!check_quote_redir(line, i))
	{
		if (line[i] == '<' && line[i - 1] != '<' && line[i + 1] != '<')
			parser->parser_left_redir = 1;
		if (line[i] == '>' && line[i - 1] != '>' && line[i + 1] != '>')
			parser->parser_right_redir = 2;
		if (line[i] == '<' && line[i + 1] == '<')
			parser->parser_dleft_redir = 3;
		if (line[i] == '>' && line[i + 1] == '>')
			parser->parser_dright_redir = 4;
	}
	if (line[i] == '\'')
		parser->parser_single_quote++;
	if (line[i] == '"')
		parser->parser_double_quote++;
}

void	parsing_handler(t_parser *parser, char *line, \
						t_env *env, char **cmds_bis)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if(line[i] == ' ')
			count++;
		i++;
	}
	if (count != ft_strlen(line))
		handler_cmd(parsing(parser, line), env, cmds_bis);
	// printf("CMD: %s || OPT: %d || ARG: %s || LEFT_REDIR : %d || RIGHT_REDIR : %d || HEREDOC : %s\n", parser->parser_cmd,parser->parser_opt,parser->parser_args, parser->parser_left_redir, parser->parser_right_redir,parser->parser_heredoc);
	free_array(cmds_bis);
	free_parser(parser);
}

void	parsing_symbols(t_parser *parser, char *line, t_env *env)
{
	int		i;
	char	**cmds;
	char	**cmds_bis;
	int		count;

	i = 0;
	cmds = NULL;
	cmds_bis = NULL;
	count = 0;
	
	while (line[i])
		parsing_redirection(line, parser, i++);
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
	parsing_handler(parser, line, env, cmds_bis);
}
