#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int				diff;

	diff = 0;
	while ((*s1 != '\0' || *s2 != '\0'))
	{
		diff = ft_memcmp(s1, s2, 1);
		if (diff != 0)
			return (diff);
		s1++;
		s2++;
	}
	return (diff);
}

char	**create_tab(t_env *env)
{
	t_element *current = env->first;

	int		i;
	int		j;
	char	**tri_tab;

	i = 0;
	j = 0;
	tri_tab = NULL;
	while(current != NULL)
	{
		current = current->next;
		i++;
	}
	current = env->first;
	tri_tab = malloc(sizeof(char *) * i + 1);
	while(current != NULL)
	{
		tri_tab[j++] = current->value;
		current = current->next;
	}
	return (tri_tab);
}

void	free_array(char **array)
{
	for (int i = 0; array[i]; i++) {
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
	array = NULL;
}