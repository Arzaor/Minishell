/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hterras <hterras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:34:02 by hterras           #+#    #+#             */
/*   Updated: 2022/07/21 17:58:55 by hterras          ###   ########.fr       */
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

void	export_arg2(t_env *env, char *value)
{
	char	**str;

	str = ft_split(value, '=');
	ft_unset(env, str[0]);
	free_array(str);
	insert_env(env, value);
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
	g_code = 0;
}
