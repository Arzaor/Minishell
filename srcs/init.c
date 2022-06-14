#include "minishell.h"

t_parser	*init()
{
	t_parser	*parser;
	
	parser = malloc(sizeof(t_parser));
	parser->parser_cmd = NULL;
	parser->parser_opt = 0;
	parser->parser_args = NULL;
	parser->parser_double_quote = 0;
	parser->parser_single_quote = 0;
	parser->parser_left_redir = 0;
	parser->parser_right_redir = 0;
	parser->parser_heredoc = NULL;
	return (parser);
}

void free_parser(t_parser *parser)
{
	free(parser->parser_cmd);
	free(parser->parser_args);
	free(parser->parser_heredoc);
	free(parser);
}