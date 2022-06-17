#include "minishell.h"

static void	ft_tri_tab(char **tri,int count)
{
	char *t;
	int j = 0;
	int i = 0;

	for(i = 0; i < count;i++)
		for(j = 0; j < count; j++)
			if(ft_strcmp(tri[i],tri[j]) < 0)
			{
				t = tri[i];
				tri[i] = tri[j];
				tri[j] = t;
			}

}

void	ft_export(t_env *env,char *value)
{
	char **tri;
	int i = 0;
	int j;
	if(value == NULL)
	{
		tri = create_tab(env);
		while(tri[i])
			i++;
		printf("%d",i);
		ft_tri_tab(tri,i);
		for(j = 0; j < i;j++)
			printf("%s\n",tri[j]);
	}
	else
		insert_env(env,value);
}