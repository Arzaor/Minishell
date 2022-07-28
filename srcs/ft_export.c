/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:34:02 by hterras           #+#    #+#             */
/*   Updated: 2022/07/28 12:54:21 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tri_tab(char **tri, int count)
{
	char	*t;
	int		j;
	int		i;

	i = 0;
	while (i < count)
	{
		while (j < count)
		{
			if (ft_strcmp(tri[i], tri[j]) < 0)
			{
				t = tri[i];
				tri[i] = tri[j];
				tri[j] = t;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

static void	export_arg3(char *split_space, t_env *env)
{
	char	*result;
	char	**split_equals;

	split_equals = ft_split(split_space, '=');
	if (split_equals[0])
	{
		result = get_env(env, split_equals[0]);
		if (result)
		{
			ft_unset(env, split_equals[0]);
			insert_env(env, split_space);
		}
		else
			insert_env(env, split_space);
		free(result);
		g_code = 0;
	}
	else
	{
		printf("minishell: export: ");
		printf("%s", split_space);
		printf(": not a valid identifier\n");
		g_code = 1;
	}
	free_array(split_equals);
}

void	export_arg(t_env *env, char *value)
{
	char	**split_space;
	int		i;

	i = 0;
	split_space = ft_split(value, ' ');
	while (split_space[i])
		export_arg3(split_space[i++], env);
	free_array(split_space);
}

void	ft_export(t_env *env, char *value)
{
	char	**tri;
	int		i;
	int		j;
	int		count;

	i = 0;
	j = 0;
	count = 0;
	if (!value)
	{
		tri = create_tab(env);
		while (tri[i])
			i++;
		count = i;
		ft_tri_tab(tri, i);
		while (j < count)
			printf("declare -x %s\n", tri[j++]);
		free(tri);
		g_code = 0;
	}
	else
		export_arg(env, value);
}
