/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 13:15:07 by jbarette          #+#    #+#             */
/*   Updated: 2022/07/26 21:25:32 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_arg3(char *split_space, t_env *env)
{
	char	*result;
	
	result = get_env(env, split_space);
	if (result)
	{
		ft_unset(env, split_space);
		insert_env(env, split_space);
	}
	else
		insert_env(env, split_space);
	free(result);
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
