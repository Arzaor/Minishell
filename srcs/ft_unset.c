/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hterras <hterras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:10:55 by jbarette          #+#    #+#             */
/*   Updated: 2022/07/05 16:40:00 by hterras          ###   ########.fr       */
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
}

void	ft_unset(t_env *env, char *arg)
{
	int		j;
	int		i;
	char	**str;
	char	**str2;

	j = 0;
	i = 0;
	str = ft_split(arg, '=');
	str2 = create_tab(env);
	while (str2[i])
	{
		if (!ft_strncmp(str2[i], str[0], ft_strlen(str[0])))
		{
			j = 1;
			break ;
		}
		i++;
	}
	if (j == 1)
		delete_element(env->first, env, arg);
	free_array(str);
	free(str2);
}
