/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hterras <hterras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:33:03 by jbarette          #+#    #+#             */
/*   Updated: 2022/07/14 13:45:51 by hterras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_i(t_parser *parser, char *line)
{
	int	i;

	i = 0;
	if (parser->parser_cmd)
		i += ft_strlen(parser->parser_cmd);
	while (line[i] == ' ')
		i++;
	if (parser->parser_opt)
	{
		if (line[i] == '-')
		{
			i++;
			while (line[i] != ' ')
				i++;
			i += 1;
		}
	}
	return (i);
}

static void	check_dollars_other(t_parser *parser, int i, t_env *env)
{
	char	*env_var;
	char	*result;
	int		count;
	int		k;

	env_var = 0;
	i += 1;
	count = i;
	k = 0;
	result = NULL;
	i = check_symbols(parser, i);
	env_var = malloc(sizeof(char) * i + 1);
	env_var = check_dollars1(count, i, env_var, parser);
	result = get_env(env, env_var);
	if (result != NULL)
	{
		parser->parser_args = malloc(sizeof(char) * ft_strlen(result) + 1);
		i = 0;
		while (result[i])
			parser->parser_args[k++] = result[i++];
		parser->parser_args[k] = '\0';
	}
	free(result);
	free(env_var);
}

static int	test1(char *line, int i, int count)
{
	while (line[i])
	{
		if ((line[i] == '>' || line[i] == '<') && !check_quote_redir(line, i))
			break ;
		count++;
		i++;
	}
	return (count);
}

static void	test2(t_parser *parser, int k, t_env *env)
{
	k = 0;
	while (parser->parser_args[k])
	{
		if (parser->parser_args[k] == '$')
		{
			check_dollars_other(parser, k, env);
			break ;
		}
		k++;
	}
}

t_parser	*parsing_args(char *line, t_parser *parser, t_env *env)
{
	int		i;
	int		k;
	int		count;

	count = 0;
	i = ft_count_i(parser, line);
	k = i;
	count = test1(line, i, count);
	i = k;
	k = 0;
	if (count > 0)
	{
		parser->parser_args = malloc(sizeof(char) * count + 1);
		while (k < count)
			parser->parser_args[k++] = line[i++];
		parser->parser_args[k] = '\0';
		if (ft_strcmp(parser->parser_cmd, "echo"))
			test2(parser, k, env);
	}
	return (parser);
}
