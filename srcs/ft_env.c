/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hterras <hterras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:45:21 by hterras           #+#    #+#             */
/*   Updated: 2022/07/05 16:23:08 by hterras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_env *env)
{
	display_linked_list(env);
}

static char	*get_env2(char **tab_env, char *path_def, int i)
{
	if (tab_env[i])
		path_def = test(tab_env, i);
	return (path_def);
}

char	*get_env(t_env *env, char *search)
{
	char	**tab_env;
	char	*path_def;
	int		i;
	int		k;
	int		count;

	count = 0;
	tab_env = create_tab(env);
	i = 0;
	k = 0;
	path_def = NULL;
	while (tab_env[i])
	{
		if (ft_strncmp(search, tab_env[i], ft_strlen(search)) == 0)
		{
			count = 1;
			break ;
		}
		if (count == 1)
			path_def = get_env2(tab_env, path_def, i);
		count = 0;
		i++;
	}
	free(tab_env);
	return (path_def);
}

char	*test(char **tab_env, int i)
{
	int		k;
	char	**path;
	char	*path_def;

	k = 0;
	path = NULL;
	path = ft_split(tab_env[i], '=');
	i = 0;
	path_def = malloc(sizeof(char) * ft_strlen(path[1]) + 1);
	while (path[1][i])
		path_def[k++] = path[1][i++];
	path_def[k] = '\0';
	free_array(path);
	return (path_def);
}
