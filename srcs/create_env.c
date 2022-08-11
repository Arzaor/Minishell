/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:03:08 by jbarette          #+#    #+#             */
/*   Updated: 2022/08/10 12:46:20 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env(char **env)
{
	int		j;
	t_env	*new_env;

	j = 0;
	new_env = init_env();
	while (env[j])
	{
		insert_env(new_env, env[j]);
		j++;
	}
	return (new_env);
}

int	insert_env(t_env *env, char *value)
{
	t_element	*new;
	char		**split_equals;

	split_equals = ft_split(value, '=');
	if (!(char_is_var_attribution(split_equals[0])))
	{
		printf("minishell: export: ");
		printf("%s", split_equals[0]);
		printf(": not a valid identifier\n");
		free_array(split_equals);
		return (1);
	}
	else
	{
		new = malloc(sizeof(*new));
		if (env == NULL || new == NULL)
			exit(EXIT_FAILURE);
		new->value = ft_strdup(value);
		new->next = env->first;
		env->first = new;
	}
	free_array(split_equals);
	return (0);
}

void	delete_env(t_env *env)
{
	t_element	*to__env;

	to__env = NULL;
	if (env == NULL)
		exit(EXIT_FAILURE);
	if (env->first != NULL)
	{
		to__env = env->first;
		env->first = env->first->next;
		free(to__env);
	}
}

void	display_linked_list(t_env *env)
{
	t_element	*current;

	current = NULL;
	if (env == NULL)
		exit(EXIT_FAILURE);
	current = env->first;
	while (current != NULL)
	{
		if (current->value != NULL)
			printf("%s\n", current->value);
		current = current->next;
	}
}
