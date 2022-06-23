#include "minishell.h"

char	*find_environment_var(t_env *env, char *env_var)
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
	while (parser->parser_args[i])
	{
		if (parser->parser_args[i] == ' ')
			break ;
		if (parser->parser_args[i] == '\'')
			break ;
		if (parser->parser_args[i] == '"')
			break ;
		if (parser->parser_args[i + 1] == '$')
			break ;
		i++;
	}
	env_var = malloc(sizeof(char) * i + 1);
	while (count < i)
	{
		env_var[k++] = parser->parser_args[count];
		count++;
	}
	env_var[k] = '\0';
	result = get_env(env, env_var);
	if (result != NULL)
		printf("%s", result);
	free (result);
	free (env_var);
	return i;
}

static int		ft_check_quote(t_parser *parser, int i, char quote, t_env *env)
{
	int		s;
	int		in_quote;

	s = 0;
	in_quote = 0;
	s = i;
	while (parser->parser_args[++i])
	{
		if (parser->parser_args[i] == quote)
		{
			in_quote = 1;
			break ;
		}
	}
	if (in_quote)
	{
		while (s < i)
		{
			if (parser->parser_args[s] == '$' && quote == '"')
				s = check_dollars(parser, s, env);
			if (parser->parser_args[s] == quote)
				s++;
			else
				printf("%c", parser->parser_args[s++]);
		}
	}
	else
		printf("Format quotes.");
	return i;
}

int		ft_show_code(t_parser *parser, int i)
{
	i += 1;
	printf("%d", g_code);
	return i;
}

void	ft_echo(t_parser *parser, t_env *env)
{
	int		i;

	i = 0;
	if (parser->parser_args)
	{
		while (parser->parser_args[i])
		{
			if (parser->parser_args[i] != '"' && parser->parser_args[i] != '\'' && parser->parser_args[i] != '$')
				printf("%c", parser->parser_args[i]);
			else if (parser->parser_args[i] == '$' && parser->parser_args[i + 1] == '?')
				i = ft_show_code(parser, i);
			else if (parser->parser_args[i] == '"' || parser->parser_args[i] == '\'')
				i = ft_check_quote(parser, i, parser->parser_args[i], env);
			else if (parser->parser_args[i] == '$' && parser->parser_args[i + 1] != '?')
				i = check_dollars(parser, i, env);
			i++;
		}
		if (!parser->parser_opt)
			printf("\n");
	}
	else
		printf("\n");
}
