#include "minishell.h"

t_env *create_env(char **env)
{
	int		j;
	t_env	*new_env;

	new_env = init_env();
	j = 0;
	while (env[j])
	{
		insert_env(new_env, env[j]);
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

t_env* unset(t_env *env,char *args)
{
	//t_env  *tmp;
	//char *value;
	//value = "ll";
	if (env == NULL)
		exit(EXIT_FAILURE);
	t_element *current = env->first;
	/*if(ft_strcmp(current->value,args))
		{
			free(env);
			return (NULL);
		}*/
	while(current != NULL)
	{
		if(!ft_strcmp(current->value,args))
		{
			printf("T: %s\n",current->value);
			printf("T: %s\n",current->next->value);

			//value = current->value;
			//current->value = current->next->value;
			//free(value);
			break;
		}
		else
		{
			printf("NOOOOOOOOO\n");
			current->value = current->next->value;
		}
		printf("T: %s\n",current->value);
	}
	return (env);
}
void ft_test(t_env *env,char *args)
{
	env = unset(env,args);
	display_linked_list(env);
}
void	display_tab(char **env_tab)
{
	int i = 0;
	while (env_tab[i])
	{
		ft_putstr_fd(env_tab[i],1);
		i++;
	}
}