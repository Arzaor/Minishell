#include "minishell.h"

static void	export_arg4(t_env *env, char **split_equals, char *split_space)
{
	char	*result;

	result = 0;
	result = get_env(env, split_equals[0]);
	if (result)
	{
		if (ft_strchr(split_space, '='))
		{
			ft_unset(env, split_equals[0]);
			g_code = insert_env(env, split_space);
		}
	}
	else
		g_code = insert_env(env, split_space);
	free(result);
}

static void	export_arg3(char *split_space, t_env *env)
{
	char	**split_equals;

	split_equals = ft_split(split_space, '=');
	if (split_equals[0])
		export_arg4(env, split_equals, split_space);
	else
	{
		printf("minishell: export: ");
		printf("%s", split_space);
		printf(": not a valid identifier\n");
		g_code = 1;
	}
	free_array(split_equals);
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
