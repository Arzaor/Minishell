/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:34:02 by hterras           #+#    #+#             */
/*   Updated: 2022/07/20 18:37:36 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	ft_tri_tab(char **tri, int count)
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

static void	export_arg2(t_env *env, char *value)
{
	char	**str;

	str = ft_split(value, '=');
	ft_unset(env, str[0]);
	free_array(str);
	insert_env(env, value);
}

static void	export_arg(t_env *env, char *value)
{
	int		j;
	int		i;
	char	**str;
	char	**str2;
	char	*str1;

	j = 0;
	i = 0;
	str = ft_split(value, ' ');
	while (str[i])
	{
		str2 = ft_split(str[i], '=');
		str1 = get_env(env, str2[0]);
		if (str1)
		{
			export_arg2(env, str[i]);
			free(str1);
		}
		else
			insert_env(env, str[i]);
		free_array(str2);
		i++;
	}
	free_array(str);
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
	}
	else
		export_arg(env, value);
}
