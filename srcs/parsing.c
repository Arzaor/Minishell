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
	parser->parser_heredoc = 0;
	return (parser);
}

static t_parser	*parsing_quotes(int count_single, int count_double, t_parser *parser)
{
	if (count_single > 0)
	{
		if (count_single % 2 == 0)
			parser->parser_single_quote = 1;
		else
			printf("Invalid single quotes\n");
	}
	if (count_double > 0)
	{
		if (count_double % 2 == 0)
			parser->parser_double_quote = 1;
		else
			printf("Invalid double quotes\n");
	}
	return (parser);
}

void	parsing_symbols(char *line)
{
	int			i;
	int			count_single;
	int			count_double;
	t_parser	*parser;

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
			count_single++;
		if (line[i] == '"')
			count_double++;
		i++;
	}
	parser = parsing_quotes(count_single, count_double, parser);
	parser = parsing_cmd(line, parser);
	// Ajout ici de la condition pour vérifier les builtins / execve
	parser = parsing_opts(line, parser);
	parser = parsing_args(line, parser);
	parser = parsing_heredoc(line, parser);
	printf("CMD : %s\nARGS : %s\nHEREDOC : %s\n", parser->parser_cmd, parser->parser_args, parser->parser_heredoc);
	// handler_cmd(parser);
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

t_parser	*parsing_args(char *line, t_parser *parser)
{
	int		i;
	int		k;
	int		count;

	i = 0;
	k = 0;
	count = 0;
	if (parser->parser_cmd)
		i = ft_strlen(parser->parser_cmd) + 1;
	if (parser->parser_opt)
		i += 3;
	k = i;
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '<')
			break ;
		count++;
		i++;
	}
	i = k;
	k = 0;
	if (count > 0)
	{
		parser->parser_args = malloc(sizeof(char) * count + 1);
		while (k < count)
			parser->parser_args[k++] = line[i++];
	}
	return (parser);
}

t_parser	*parsing_heredoc(char *line, t_parser *parser)
{
	int		i;
	int		k;
	int		count;

	i = 0;
	k = 0;
	count = 0;
	if (parser->parser_right_redir || parser->parser_left_redir)
	{
		while (line[i] != '>' && line[i] != '<')
			i++;
		if (line[i + 1] == '>' || line[i + 1] == '<')
			i += 3;
		else
			i += 2;
		k = i;
		while (line[i])
		{
			count++;
			i++;
		}
		i = k;
		k = 0;
		if (count > 0)
		{
			parser->parser_heredoc = malloc(sizeof(char) * count + 1);
			while (line[i])
			{
				parser->parser_heredoc[k++] = line[i];
				i++;
			}
		}
	}
	return (parser);
}