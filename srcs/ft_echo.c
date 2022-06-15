#include "minishell.h"

void ft_echo(t_parser *parser)
{
	int i;

	i = 0;
	if (parser->parser_args)
	{
		if (!parser->parser_single_quote && !parser->parser_double_quote)
			printf("%s", parser->parser_args);
		if ((parser->parser_single_quote % 2 != 0) && (parser->parser_single_quote % 2 != 0))
			printf("Error quotes.");
		else if ((parser->parser_single_quote % 2 != 0) || (parser->parser_single_quote % 2 != 0))
		{
			while (parser->parser_args[i])
			{
				if (parser->parser_args[i] == '\'')
				{
					int k = 0;
					while (parser->parser_args[k])
					{
						if (parser->parser_args[k] == '"')
							printf("%c", parser->parser_args[i]);
						else
							i++;
						k++;
					}
				}
				i++;
			}
		}
		if (!parser->parser_opt)
			printf("\n");
	}
	else
		printf("\n");
}