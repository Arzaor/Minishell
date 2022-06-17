#include "minishell.h"

void	ft_cd(t_parser *parser)
{
	if (chdir(parser->parser_args) == -1)
		printf("Chemin inconnu.");
}