/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 14:53:21 by jbarette          #+#    #+#             */
/*   Updated: 2022/07/27 16:17:42 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_var_env1(char *env_def, int count, t_parser *parser)
{
	int	k;

	k = 0;
	if (count)
	{
		if (env_def)
			parser->parser_count += ft_strlen(env_def);
	}
	else
	{
		if (env_def)
		{
			while (env_def[k])
				parser->parser_arguments[parser->parser_count++] = env_def[k++];
		}
	}
}

static char	*get_var_env2(t_parser *parser, int i, char *var_env)
{
	int	k;

	k = 0;
	while (parser->parser_args[i] && ft_isalnum(parser->parser_args[i]))
		var_env[k++] = parser->parser_args[i++];
	var_env[k] = '\0';
	return (var_env);
}

int	get_var_env(t_parser *parser, int i, t_env *env, int count)
{
	char	*var_env;
	char	*env_def;
	int		length;
	int		tmp;

	var_env = 0;
	env_def = 0;
	i += 1;
	tmp = i;
	length = 0;
	while (parser->parser_args[i] && ft_isalnum(parser->parser_args[i]))
	{
		length++;
		i++;
	}
	var_env = malloc(sizeof(char) * length + 1);
	var_env = get_var_env2(parser, tmp, var_env);
	env_def = get_env(env, var_env);
	get_var_env1(env_def, count, parser);
	free(env_def);
	free(var_env);
	return (i);
}
