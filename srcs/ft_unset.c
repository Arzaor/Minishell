/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:10:55 by jbarette          #+#    #+#             */
/*   Updated: 2022/07/26 19:08:47 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_element	*delete_element(t_element *element, t_env *env, char *arg)
{
	t_element	*current;
	t_element	*precent;
	char		**split_arg;

	current = element;
	split_arg = ft_split(current->value, '=');
	if (element == NULL)
		return (NULL);
	if (ft_strncmp(arg, split_arg[0], ft_strlen(split_arg[0])) == 0)
	{
		precent = current->next;
		if (current == env->first)
			env->first = precent;
		free(current->value);
		free(current);
		free_array(split_arg);
		return (precent);
	}
	else
	{
		element->next = delete_element(element->next, env, arg);
		free_array(split_arg);
		return (element);
	}
	return (NULL);
}

void	ft_unset(t_env *env, char *arg)
{
	char	*str;

	if (arg)
	{
		str = get_env(env, arg);
		if (str)
		{
			delete_element(env->first, env, arg);
			free(str);
		}
	}
}
