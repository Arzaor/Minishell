/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hterras <hterras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:34:02 by hterras           #+#    #+#             */
/*   Updated: 2022/06/25 15:34:16 by hterras          ###   ########.fr       */
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

void static export_arg(t_env *env, char *value)
{
	int		j;
	int		i;
	char	**str;
	char	**str2;

	j = 0;
	i = 0;
	str = ft_split(value,'=');
	str2 = create_tab(env);
	while (str2[i])
	{
		if(!ft_strncmp(str2[i],str[0],ft_strlen(str[0])))
		{
			j = 1;
			break;
		}
		i++;
	}
	if (j == 1)
	{
		ft_unset(env,value);
		insert_env(env, value);
	}
	else
		insert_env(env,value);
	free_array(str);
	free(str2);
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
		export_arg(env,value);
}
