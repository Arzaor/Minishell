#include "minishell.h"

static void	ft_tri_tab(char **tri,int count)
{
	char *t;
	int j;
	int i = 0;

	while(i < count)
	{
		while(j < count)
		{
			if(ft_strcmp(tri[i],tri[j]) > 0)
			{
				t = tri[i];
				tri[i] = tri[j];
				tri[j] = t;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

void	ft_export(t_env *env, char *value)
{
	char **tri;
	int i = 0;
	int count = 0;
	if(value == NULL)
	{
		tri = create_tab(env);
		while(tri[i])
			i++;
		count = i - 1;
		ft_tri_tab(tri,i);
		while(count >= 0)
     		printf("declare -x %s\n ", tri[count--]);
		free(tri);
	}
	else
		insert_env(env,value);
}