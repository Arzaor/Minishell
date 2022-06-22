#include "minishell.h"

static void delete_element(t_element *element, t_env *env, char *arg)
{
	t_element *current = element;
	while ((element = element->next) != NULL)
	{
		if (ft_strncmp(arg, element->value, ft_strlen(arg)) == 0)
		{
			current->next = element->next;
			free(element->value);
			free(element);
			break ;
		}
		current = element;
	}
}

void	ft_unset(t_env *env, char *arg)
{
	if (arg)
		delete_element(env->first, env, arg);
}
