/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 13:15:07 by jbarette          #+#    #+#             */
/*   Updated: 2022/07/25 13:26:07 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	concat_expansion(char **split_equals, char *result, t_env *env)
{
	char	*bin;

	bin = (char *)ft_calloc(sizeof(char), \
		(ft_strlen(split_equals[0]) + 1 + ft_strlen(result) + 1));
	ft_strcat(bin, split_equals[0]);
	ft_strcat(bin, "=");
	ft_strcat(bin, result);
	result = get_env(env, split_equals[0]);
	if (result)
		export_arg2(env, bin);
	else
		insert_env(env, bin);
	free(bin);
	free(result);
}

void	export_w_expansion(t_env *env, char **split_equals, \
			char **split_space, int i)
{
	char	*result;

	result = get_env(env, split_equals[0]);
	if (result)
		export_arg2(env, split_space[i]);
	else
		insert_env(env, split_space[i]);
	free(result);
}

static void	export_arg3(char **split_space, t_env *env)
{
	char	**split_equals;
	int		i;

	i = 0;
	while (split_space[i])
	{
		split_equals = ft_split(split_space[i], '=');
		export_w_expansion(env, split_equals, split_space, i);
		free_array(split_equals);
		i++;
	}
}

void	export_arg(t_env *env, char *value)
{
	char	**split_space;

	(void)env;
	split_space = ft_split(value, ' ');
	export_arg3(split_space, env);
	free_array(split_space);
}
