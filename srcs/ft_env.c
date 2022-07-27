/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:45:21 by hterras           #+#    #+#             */
/*   Updated: 2022/07/27 14:36:43 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_env *env)
{
	display_linked_list(env);
}

char	*get_env2(char **tab_env, int i)
{
	char	*path_def;

	path_def = 0;
	if (tab_env[i])
		path_def = test(tab_env, i);
	return (path_def);
}

static char	*get_path(char **tab_env, char *search, int i, char *path_def)
{
	char	**split_equals;
	int		count;

	count = 0;
	split_equals = NULL;
	while (tab_env[i])
	{
		split_equals = ft_split(tab_env[i], '=');
		if (ft_strncmp(search, split_equals[0], \
			ft_strlen(split_equals[0])) == 0)
		{
			count = 1;
			free_array(split_equals);
			break ;
		}
		free_array(split_equals);
		i++;
	}
	if (count == 1)
		path_def = get_env2(tab_env, i);
	free(tab_env);
	return (path_def);
}

char	*get_env(t_env *env, char *search)
{
	char	**tab_env;
	int		i;
	char	*path_def;

	i = 0;
	path_def = NULL;
	tab_env = create_tab(env);
	path_def = get_path(tab_env, search, i, path_def);
	return (path_def);
}

char	*test(char **tab_env, int i)
{
	int		k;
	char	**path;
	char	*path_def;

	k = 0;
	path = ft_split(tab_env[i], '=');
	i = 0;
	if (path[1])
	{
		path_def = malloc(sizeof(char) * ft_strlen(path[1]) + 1);
		while (path[1][i])
			path_def[k++] = path[1][i++];
		path_def[k] = '\0';
	}
	else
	{
		path_def = malloc(sizeof(char) * ft_strlen(path[0]) + 1);
		while (path[0][i])
			path_def[k++] = path[0][i++];
		path_def[k] = '\0';
	}
	free_array(path);
	return (path_def);
}
