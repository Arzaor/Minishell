/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:27:36 by jbarette          #+#    #+#             */
/*   Updated: 2022/07/26 16:45:51 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_bin(char **path_split, t_parser *parser)
{
	char	*bin;
	int		i;

	bin = NULL;
	i = 0;
	while (path_split[i])
	{
		bin = (char *)ft_calloc(sizeof(char), \
			(ft_strlen(path_split[i]) + 1 + ft_strlen(parser->parser_cmd) + 1));
		if (bin == NULL)
			break ;
		ft_strcat(bin, path_split[i]);
		ft_strcat(bin, "/");
		ft_strcat(bin, parser->parser_cmd);
		if (access(bin, F_OK) == 0)
		{
			free(parser->parser_cmd);
			parser->parser_cmd = NULL;
			break ;
		}
		free(bin);
		bin = NULL;
		i++;
	}
	return (bin);
}

void	get_absolute_path(char *path, t_parser *parser)
{
	char	**path_split;
	char	*bin;

	path_split = NULL;
	bin = NULL;
	if (path != NULL)
	{
		path_split = ft_split(path, ':');
		free(path);
		bin = create_bin(path_split, parser);
		free_array(path_split);
		if (bin)
			parser->parser_cmd = bin;
	}
}
