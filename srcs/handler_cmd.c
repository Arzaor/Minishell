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

static void	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
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

void	create_cmd(t_parser *parser, char **env)
{
	char	**new_env;

	new_env = create_env(env);
	if (!ft_strncmp(parser->parser_cmd, "echo", 3))
		ft_echo(parser);
	if (!ft_strncmp(parser->parser_cmd, "cd", 2))
		printf("cd");
	if (!ft_strncmp(parser->parser_cmd, "pwd", 3))
		pwd();
	if (!ft_strncmp(parser->parser_cmd, "export", 6))
		printf("export");
	if (!ft_strncmp(parser->parser_cmd, "unset", 5))
		printf("unset");
	if (!ft_strncmp(parser->parser_cmd, "env", 3))
		ft_env(env);
}

void	handler_cmd(t_parser *parser, char **env)
{
	if (is_build_in(parser->parser_cmd))
		create_cmd(parser, env);
	else
		printf("command pas a faire a geres");
	(void)parser;
}
