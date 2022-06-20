#include "minishell.h"

t_parser	*save_heredoc(t_parser *parser, int count, int i, char *line)
{
	int		k;

	k = 0;
	if (count > 0)
	{
		parser->parser_heredoc = malloc(sizeof(char) * count + 1);
		while (line[i] && line[i] != ' ')
		{
			parser->parser_heredoc[k++] = line[i];
			i++;
		}
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
	if (parser->parser_right_redir || parser->parser_left_redir || parser->parser_dright_redir || parser->parser_dleft_redir)
	{
		while (line[i] != '>' && line[i] != '<')
			i++;
		if (line[i + 1] == '>' || line[i + 1] == '<')
			i += 3;
		else
			i += 2;
		k = i;
		while (line[i] && line[i] != ' ')
		{
			count++;
			i++;
		}
		parser = save_heredoc(parser, count, k, line);	
	}
	return (parser);
}