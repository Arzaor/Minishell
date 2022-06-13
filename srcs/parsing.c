#include "minishell.h"

t_parser	*init()
{
	t_parser	*parser;
	
	parser = malloc(sizeof(t_parser));
	parser->parser_cmd = NULL;
	parser->parser_opt = NULL;
	parser->parser_args = NULL;
	parser->parser_double_quote = 0;
	parser->parser_single_quote = 0;
	parser->parser_left_redir = 0;
	parser->parser_right_redir = 0;
	parser->parser_heredoc = 0;

	return (parser);
}

void	parsing_symbols(char *line)
{
	int			i;
	t_parser	*parser;

	i = 0;
	parser = init();
	while (line[i])
	{
		if (line[i] == '<')
			parser->parser_left_redir = 1;
		if (line[i] == '>')
			parser->parser_right_redir = 1;
		if (line[i] == '\'')
			parser->parser_single_quote = 1;
		if (line[i] == '"')
			parser->parser_double_quote = 1;
		i++;
	}
	parser = parsing_cmd(line, parser);
}

t_parser	*parsing_cmd(char *line, t_parser *parser)
{
	int		i;
	int		y;
	int		count;

	i = 0;	
	y = 0;
	count = 0;
	while (line[i])
	{
		if (ft_isalpha(line[i]))
			count++;
		else
			break ;
		i++;
	}
	parser->parser_cmd = malloc(sizeof(char) * count + 1);
	i = 0;
	while (i < count)
		parser->parser_cmd[y++] = line[i++];
	return (parser);
}
