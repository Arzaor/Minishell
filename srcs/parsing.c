/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hterras <hterras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:37:10 by jbarette          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/07/06 13:56:51 by jbarette         ###   ########.fr       */
=======
/*   Updated: 2022/07/06 14:17:19 by hterras          ###   ########.fr       */
>>>>>>> 66789f435c97597aaccd9e85454f5ac1a5e8cd02
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_parser	*parsing(t_parser *parser, char *line)
{
	int	i;

	i = 1;
	parser = parsing_cmd(line, parser);
	if (!strcmp(parser->parser_cmd, "cat") || \
		!strcmp(parser->parser_cmd, "sort"))
		g_code = -111;
	parser = parsing_opts(line, parser);
	parser = parsing_args(line, parser);
	if (parser->parser_right_redir == 2 || parser->parser_left_redir == 1 || \
		parser->parser_dright_redir == 4 || parser->parser_dleft_redir == 3)
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
		if (line[i] == ' ')
			count++;
		i++;
	}
	if (count != ft_strlen(line))
		handler_cmd(parsing(parser, line), env, cmds_bis);
	free_array(cmds_bis);
	free_parser(parser);
}

void	parsing_symbols(t_parser *parser, char *line, t_env *env)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (line[i])
		parsing_redirection(line, parser, i++);
	if(g_code != 130 && g_code != 131)
	{
		signal(SIGQUIT, sig_handler2);
		signal(SIGINT, sig_handler2);
	}
	
	parsing_handler(parser, line, env, fast_parsing(parser, line));
}
