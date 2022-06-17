#include "minishell.h"

void	ft_echo(t_parser *parser)
{
	int		i;
	int		k;
	int		in_quote;
	int		s;
	char	*arg;
	char	*new_arg;

	i = 0;
	k = 0;
	in_quote = 0;
	s = 0;
	arg = parser->parser_args;
	new_arg = malloc(sizeof(char) * ft_strlen(parser->parser_args) + 1);
	while (arg[i])
	{
		if (arg[i] != '"' && arg[i] != '\'')
			new_arg[k++] = arg[i];
		else if (arg[i] == '"')
		{
			s = i;
			while (arg[++i])
			{
				if (arg[i] == '"')
				{
					in_quote = 1;
					break ;
				}
			}
			// i = deuxième guillemet
			// s = premier guillemet
			if (in_quote)
			{
				while (++s < i)
				{
					if (arg[s] == '"')
						s++;
					new_arg[k++] = arg[s];
				}
			}
			else
			{
				printf("Format quotes.");
				break ;
			}
			in_quote = 0;
		}
		else if (arg[i] == '\'')
		{
			s = i;
			while (arg[++i])
			{
				if (arg[i] == '\'')
				{
					in_quote = 1;
					break ;
				}
			}
			if (in_quote)
			{
				while (++s < i)
				{
					if (arg[s] == '\'')
						s++;
					new_arg[k++] = arg[s];
				}
			}
			else
			{
				printf("Format quotes.");
				break ;
			}
			in_quote = 0;
		}
		i++;
	}
	printf("%s", new_arg);
	if (!parser->parser_opt || !parser->parser_args)
		printf("\n");
}