/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:33:03 by jbarette          #+#    #+#             */
/*   Updated: 2022/07/27 13:55:24 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_option(char *line, int i, t_parser *parser)
{
	char	letter;
	int		count;

	letter = 0;
	count = 0;
	if (line[i] == '-')
	{
		i++;
		while (line[i] == 'n')
		{
			i++;
			count++;
			letter = line[i];
		}
		if (letter != 'n' && letter != ' ')
		{
			i -= count + 2;
			parser->parser_opt = 0;
		}
		i += 1;
	}
	return (i);
}

static int	count_cursor(t_parser *parser, char *line)
{
	int		i;

	i = 0;
	if (parser->parser_cmd)
		i += ft_strlen(parser->parser_cmd);
	while (line[i] == ' ')
		i++;
	if (parser->parser_opt)
		i = count_option(line, i, parser);
	return (i);
}

static int	get_var_env(t_parser *parser, int i, t_env *env)
{
	char	*var_env;
	char	*env_def;
	int		length;
	int		tmp;
	int		k;

	var_env = 0;
	env_def = 0;
	i += 1;
	tmp = i;
	k = 0;
	length = 0;
	while (parser->parser_args[i] && (ft_isalnum(parser->parser_args[i])))
	{
		length++;
		i++;
	}
	var_env = malloc(sizeof(char) * length + 1);
	i = tmp;
	while (parser->parser_args[i] && (ft_isalnum(parser->parser_args[i])))
		var_env[k++] = parser->parser_args[i++];
	var_env[k] = '\0';
	env_def = get_env(env, var_env);
	if (env_def)
		parser->parser_count += ft_strlen(env_def);
	free(env_def);
	free(var_env);
	return (i);
}

static int		found_second_quote(t_parser *parser, char *arg, int i, char quote, t_env *env)
{
	int	result;
	int	tmp;

	result = 0;
	if (arg[i + 1])
		i += 1;
	else
		return (-1);
	tmp = i;
	while (arg[i])
	{
		if (arg[i] == quote)
		{
			result = 1;
			break ;
		}
		i++;
	}
	i = tmp;
	if (result)
	{
		if (quote == '\'')
		{
			while (arg[i] != quote)
			{
				parser->parser_count++;
				i++;
			}
		}
		else
		{
			while (arg[i] != quote)
			{
				if (arg[i] == '$' && arg[i + 1] != '?')
					i = get_var_env(parser, i, env);
				else if (arg[i] == '$' && arg[i + 1] == '?')
				{
					if (ft_strlen(ft_itoa_base(g_code, 10)) > 0)
						parser->parser_count += ft_strlen(ft_itoa_base(g_code, 10));
					else
						parser->parser_count++;
					i += 2;
				}
				else
				{
					parser->parser_count++;
					i++;
				}
			}
		}
	}
	else
		return (-1);
	return (i);
}

static int	transform_arg(t_parser *parser, t_env *env)
{
	int	i;

	i = 0;
	while (parser->parser_args[i])
	{
		if (parser->parser_args[i] != '\'' && parser->parser_args[i] != '"' && parser->parser_args[i] != '$')
		{
			parser->parser_count++;
			i++;
		}
		else if (parser->parser_args[i] == '\'' || parser->parser_args[i] == '"')
		{
			i = found_second_quote(parser, parser->parser_args, i, parser->parser_args[i], env);
			if (i == -1)
			{
				printf("Erreur : Format quote.");
				return (0);
				break ;
			}
			if (parser->parser_args[i] == '\'' || parser->parser_args[i] == '"')
				i += 1;
		}
		else if (parser->parser_args[i] == '$' && parser->parser_args[i + 1] != '?')
			i = get_var_env(parser, i, env);
		else if (parser->parser_args[i] == '$' && parser->parser_args[i + 1] == '?')
		{
			if (ft_strlen(ft_itoa_base(g_code, 10)) > 0)
				parser->parser_count += ft_strlen(ft_itoa_base(g_code, 10));
			else
				parser->parser_count++;
			i += 2;
		}
	}
	return (1);
}

t_parser	*parsing_args(char *line, t_parser *parser, t_env *env)
{
	int	start;
	int	tmp;
	int	i;

	start = count_cursor(parser, line);
	tmp = start;
	i = 0;
	if (line[start])
	{
		while (line[start])
			start++;
		parser->parser_args = malloc(sizeof(char) * start - tmp + 1);
		start = tmp;
		while (line[start])
			parser->parser_args[i++] = line[start++]; 
		parser->parser_args[i] = '\0';
		tmp = transform_arg(parser, env);
		if (tmp)
			save_to_arg(parser, env);
		else
			parser->parser_args = NULL;
	}
	else
		parser->parser_args = NULL;
	return (parser);
}
