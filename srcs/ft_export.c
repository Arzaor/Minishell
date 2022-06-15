#include "minishell.h"

void	ft_export(t_parser *parser, t_env *env)
{
	if (parser->parser_args)
		insert_env(env, parser->parser_args);
}