/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:34:02 by hterras           #+#    #+#             */
/*   Updated: 2022/08/06 18:29:01 by jbarette         ###   ########.fr       */
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

static void	ft_export2(char **tri, int count, int i)
{
	int	j;

	j = 0;
	while (j < count)
	{
		printf("declare -x ");
		while (tri[j][i])
		{
			if (tri[j][i] == '=')
			{
				printf("%c", tri[j][i]);
				i += 1;
				printf("\"");
			}
			printf("%c", tri[j][i]);
			i++;
		}
		if (ft_strchr(tri[j], '='))
			printf("\"");
		printf("\n");
		i = 0;
		j++;
	}
	free(tri);
}

void	ft_export(t_env *env, char *value)
{
	char	**tri;
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (!value)
	{
		tri = create_tab(env);
		while (tri[i])
			i++;
		count = i;
		ft_tri_tab(tri, i);
		ft_export2(tri, count, i);
		g_code = 0;
	}
	else
		export_arg(env, value);
}
