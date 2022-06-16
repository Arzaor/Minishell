#include "minishell.h"

static void	pwd(void)
{
	char	pwd[256];

	if (getcwd(pwd, sizeof(pwd)) != NULL)
		printf("%s\n", pwd);
	else
		perror("getcwd() error");
}
/*static void	free_array(char **array)
{
	for (int i = 0; array[i]; i++) {
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
	array = NULL;
}*/

static void	ft_env(t_env *env)
{
	display_linked_list(env);
}

static bool	is_build_in(char *cmd)
{
	const char	*built_in[7];
	int			i;

	i = 0;
	built_in[0] = "echo";
	built_in[1] = "cd";
	built_in[2] = "pwd";
	built_in[3] = "export";
	built_in[4] = "unset";
	built_in[5] = "env";
	built_in[6] = NULL;
	while (built_in[i])
	{
		if (!ft_strcmp(built_in[i], cmd))
			return (true);
		i++;
	}
	return (false);
}

static char **create_tab(t_env *env)
{
	t_element *current = env->first;

	int i = 0;
	int j = 0;
	char **tri_tab;

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
	i = 0;
	while (tri_tab[i])
		printf("%s\n", tri_tab[i++]);
	return (tri_tab);
}

void	ft_export(t_env *env,char *value)
{
	char **tri;
	if(value == NULL)
	{
		tri = create_tab(env);
		free(tri);
	}
	else
		insert_env(env,value);
}
void	create_cmd(t_parser *parser, t_env *env)
{
	if (!ft_strncmp(parser->parser_cmd, "echo", 3))
		ft_echo(parser);
	if (!ft_strncmp(parser->parser_cmd, "cd", 2))
		printf("cd");
	if (!ft_strncmp(parser->parser_cmd, "pwd", 3))
		pwd();
	if (!ft_strncmp(parser->parser_cmd, "export", 6))
		ft_export(env,parser->parser_args);
	if (!ft_strncmp(parser->parser_cmd, "unset", 5))
		printf("unset");
	if (!ft_strncmp(parser->parser_cmd, "env", 3))
		ft_env(env);
}

void	handler_cmd(t_parser *parser, t_env *env)
{
	if (is_build_in(parser->parser_cmd))
		create_cmd(parser, env);
	else
		printf("command pas a faire a geres");
	(void)parser;
}
