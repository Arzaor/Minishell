#include "minishell.h"

static char	*find_environment_var(t_env *env, char *env_var)
{
	char **split_env;

	split_env = NULL;
	if (env == NULL)
		exit(EXIT_FAILURE);
	t_element *current = env->first;
	while (current != NULL)
	{
		if (current->value != NULL)
		{
			split_env = ft_split(current->value, '=');
			if (ft_strncmp(env_var, split_env[0], ft_strlen(split_env[0])) == 0)
				return split_env[1];
		}
		current = current->next;
	}
	return NULL;
}

static int	check_dollars(t_parser *parser, int i, t_env *env)
{
	char	*env_var;
	int		count;
	int		k;
	char *result;

	env_var = 0;
	i += 1;
	count = i;
	k = 0;
	result = NULL;
	while (parser->parser_args[i] && parser->parser_args[i] != ' ')
		i++;
	env_var = malloc(sizeof(char) * i + 1);
	while (count <= i)
	{
		env_var[k++] = parser->parser_args[count];
		count++;
	}
	result = find_environment_var(env, env_var);
	if (result != NULL)
		printf("%s", result);
	return i - 1;
}
void	ft_echo(t_parser *parser, t_env *env)
{
	int		i;
	int		k;
	int		s;
	int		in_quote;
	char	*new_arg;

	i = 0;
	k = 0;
	s = 0;
	in_quote = 0;
	new_arg = malloc(sizeof(char) * ft_strlen(parser->parser_args) + 1);
	while (parser->parser_args[i])
	{
		if (parser->parser_args[i] != '"' && parser->parser_args[i] != '\'' && parser->parser_args[i] != '$')
			new_arg[k++] = parser->parser_args[i];
		else if (parser->parser_args[i] == '"')
		{
			s = i;
			while (parser->parser_args[++i])
			{
				if (parser->parser_args[i] == '"')
				{
					in_quote = 1;
					break ;
				}
			}
			if (in_quote)
			{
				while (++s < i)
				{
					if (parser->parser_args[s] == '"')
						s++;
					new_arg[k++] = parser->parser_args[s];
				}
			}
			else
			{
				printf("Format quotes.");
				break ;
			}
			in_quote = 0;
		}
		else if (parser->parser_args[i] == '\'')
		{
			s = i;
			while (parser->parser_args[++i])
			{
				if (parser->parser_args[i] == '\'')
				{
					in_quote = 1;
					break ;
				}
			}
			if (in_quote)
			{
				while (++s < i)
				{
					if (parser->parser_args[s] == '\'')
						s++;
					new_arg[k++] = parser->parser_args[s];
				}
			}
			else
			{
				printf("Format quotes.");
				break ;
			}
			in_quote = 0;
		}
		else if (parser->parser_args[i] == '$')
			i = check_dollars(parser, i, env);
		i++;
	}
	printf("%s", new_arg);
	if (!parser->parser_opt || !parser->parser_args)
		printf("\n");
}
