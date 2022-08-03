/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 14:53:21 by jbarette          #+#    #+#             */
/*   Updated: 2022/08/03 16:43:02 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_var_env_cmd1(char *env_def, int count, t_parser *parser)
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
				parser->parser_commands[parser->parser_count++] = env_def[k++];
		}
	}
}

static char	*get_var_env_cmd2(t_parser *parser, int i, char *var_env)
{
	int	k;

	k = 0;
	while (parser->parser_cmd[i] && ft_isalnum(parser->parser_cmd[i]))
		var_env[k++] = parser->parser_cmd[i++];
	var_env[k] = '\0';
	return (var_env);
}

int	get_var_env_cmd(t_parser *parser, int i, t_env *env, int count)
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
	while (parser->parser_cmd[i] && ft_isalnum(parser->parser_cmd[i]))
	{
		length++;
		i++;
	}
	var_env = malloc(sizeof(char) * length + 1);
	var_env = get_var_env_cmd2(parser, tmp, var_env);
	env_def = get_env(env, var_env);
	get_var_env_cmd1(env_def, count, parser);
	free(env_def);
	free(var_env);
	return (i);
}
