#include "minishell.h"

t_env	*create_env(char **env)
{
	int		i;
	int		k, j;
	t_env	*new_env;

	i = 0;
	k = 0;
	new_env = init_env();
	while (env[i])
		i++;
	j = 0;
	while (env[j])
	{
		insert_env(new_env, env[j]);
		k++;
		j++;
	}
	return (new_env);
}

void	insert_env(t_env *env, char *value)
{
	t_element	*new;

	new = malloc(sizeof(*new));
	if (env == NULL || new == NULL)
		exit(EXIT_FAILURE);
	new->value = ft_strdup(value);
	new->next = env->first;
	env->first = new;
}

void	delete_env(t_env *env)
{
	if (env == NULL)
		exit(EXIT_FAILURE);
	if (env->first != NULL)
	{
		t_element *to_delete_env = env->first;
		env->first = env->first->next;
		free(to_delete_env);
	}
}

void	display_linked_list(t_env *env)
{
	if (env == NULL)
		exit(EXIT_FAILURE);
	t_element *current = env->first;
	while (current != NULL)
	{
		if (current->value != NULL)
			printf("%s\n", current->value);
		current = current->next;
	}
}

void	display_tab(char **env_tab)
{
	int i = 0;
	while (env_tab[i])
	{
		printf("%s\n", env_tab[i]);
		i++;
	}
}