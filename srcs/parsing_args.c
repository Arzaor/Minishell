/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:33:03 by jbarette          #+#    #+#             */
/*   Updated: 2022/08/01 12:09:21 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		parser->parser_count_arg = ft_strlen(parser->parser_args);
		tmp = transform_arg(parser, env);
		if (!parser->parser_error)
			save_to_arg(parser, env);
	}
	return (parser);
}
