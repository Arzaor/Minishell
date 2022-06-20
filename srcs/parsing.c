#include "minishell.h"

static t_parser	*parsing(t_parser *parser, char *line)
{
	parser = parsing_cmd(line, parser);
	parser = parsing_opts(line, parser);
	parser = parsing_args(line, parser);
	parser = parsing_heredoc(line, parser);
	return (parser);
}

t_parser	*parsing_cmd(char *line, t_parser *parser)
{
	int		i;
	int		y;
	int		count;

	i = 0;	
	y = 0;
	count = 0;
	while (ft_isalpha(line[i]))
		i++;
	parser->parser_cmd = malloc(sizeof(char) * i + 1);
	while (count < i)
		parser->parser_cmd[y++] = line[count++];
	parser->parser_cmd[y] = '\0';
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

void	parsing_symbols(char *line, t_env *env)
{
	int			i;
	int			count_single;
	int			count_double;
	t_parser	*parser;
	char		**cmds;

	i = 0;
	count_single = 0;
	count_double = 0;
	parser = init();
	while (line[i])
	{
		if (line[i] == '<')
			parser->parser_left_redir = 1;
		if (line[i] == '>')
			parser->parser_right_redir = 1;
		if (line[i] == '\'')
			parser->parser_single_quote++;
		if (line[i] == '"')
			parser->parser_double_quote++;
		i++;
	}
	cmds = ft_split(line, ' ');
	i = 0;
	while (cmds[i])
	{
		if (cmds[i][0] == '>')
			cmds[i] = NULL;
		i++;
	}
	handler_cmd(parsing(parser, line), env, cmds);
	printf("CMD: %s || OPT: %d || ARG: %s || LEFT_REDIR : %d || RIGHT_REDIR : %d || HEREDOC : %s\n", parser->parser_cmd,parser->parser_opt,parser->parser_args, parser->parser_left_redir, parser->parser_right_redir,parser->parser_heredoc);
	free_array(cmds);
	free_parser(parser);
}