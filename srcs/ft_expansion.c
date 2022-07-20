/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:05:02 by jbarette          #+#    #+#             */
/*   Updated: 2022/07/20 17:34:11 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_symbols(t_parser *parser, int i)
{
	while (parser->parser_args[i])
	{
		if (parser->parser_args[i] == ' ')
			break ;
		if (parser->parser_args[i] == '\'')
			break ;
		if (parser->parser_args[i] == '"')
			break ;
		if (parser->parser_args[i] == '$')
			break ;
		if (parser->parser_args[i] == '(' || parser->parser_args[i] == ')')
			break ;
		i++;
	}
	return (i);
}

char	*check_dollars1(int count, int i, char *env_var, t_parser *parser)
{
	int	k;

	k = 0;
	while (count < i)
	{
		env_var[k++] = parser->parser_args[count];
		count++;
	}
	env_var[k] = '\0';
	return (env_var);
}

int	check_dollars(t_parser *parser, int i, t_env *env)
{
	char	*env_var;
	char	*result;
	int		count;

	env_var = 0;
	i += 1;
	count = i;
	result = NULL;
	i = check_symbols(parser, i);
	env_var = malloc(sizeof(char) * i + 1);
	env_var = check_dollars1(count, i, env_var, parser);
	result = get_env(env, env_var);
	if (result != NULL)
		printf("%s", result);
	free(result);
	free(env_var);
	return (i);
}

int	check_dollars_w_quote(t_parser *parser, int i, t_env *env)
{
	char	*env_var;
	char	*result;
	int		count;

	env_var = 0;
	i += 1;
	count = i;
	result = NULL;
	i = check_symbols(parser, i);
	env_var = malloc(sizeof(char) * i + 1);
	env_var = check_dollars1(count, i, env_var, parser);
	result = get_env(env, env_var);
	if (result != NULL)
		printf("%s", result);
	free(result);
	free(env_var);
	if (parser->parser_args[i] == '\'' || parser->parser_args[i] == '"')
		return (i);
	else
		return (i + 1);
}
