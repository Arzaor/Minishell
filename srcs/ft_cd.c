#include "minishell.h"

void	ft_cd(t_parser *parser)
{
	if (chdir(parser->parser_args) == -1)
	{
		printf("bash: cd: %s: No such file or directory\n", parser->parser_args);
		g_code = 1;
	}
	else
		g_code = 0;
}