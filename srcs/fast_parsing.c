/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fast_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:46:23 by jbarette          #+#    #+#             */
/*   Updated: 2022/08/02 16:25:11 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**fast_parsing(char *line, t_parser *parser)
{
	int		count;
	int		count_dim;
	char	*bin;
	char	**cmds_bis;

	count = 0;
	count_dim = 0;
	bin = 0;
	cmds_bis = NULL;
	if (parser->parser_args)
	{
		count = ft_strlen(line);
		count_dim = ft_strlen(line) - parser->parser_count_arg;
		while (count >= count_dim)
			line[count--] = '\0';
		bin = (char *)ft_calloc(sizeof(char), \
				(ft_strlen(line) + 1 + ft_strlen(parser->parser_args) + 1));
		strcat(bin, line);
		strcat(bin, parser->parser_args);
		cmds_bis = ft_split(bin, ' ');
		free(bin);
	}
	else
		cmds_bis = ft_split(line, ' ');
	return (cmds_bis);
}
