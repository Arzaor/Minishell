#include "minishell.h"

t_parser	*parsing_args(char *line, t_parser *parser)
{
	int		i;
	int		k;
	int		count;

	i = 0;
	k = 0;
	count = 0;
	if (parser->parser_cmd)
		i += ft_strlen(parser->parser_cmd);
	if (line[i] == ' ')
		i++;
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
