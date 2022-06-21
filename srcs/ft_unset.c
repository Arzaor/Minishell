#include "minishell.h"

static t_element* delete_element(t_element *element, t_env *env, char *arg)
{
    t_element *current;
	t_element *precent;

    current = element;
	precent = NULL;
    if (element == NULL)
        return NULL;
    if (ft_strncmp(arg, current->value, ft_strlen(arg)) == 0)
    {
        precent = current->next;
		if (current == env->first)
			env->first = precent;
        free(current);
        return precent;
    }
	else
    {
        element->next = delete_element(element->next, env, arg);
        return element;
    }
}

void	ft_unset(t_env *env, char *arg)
{
	if (arg)
		delete_element(env->first, env, arg);
}
