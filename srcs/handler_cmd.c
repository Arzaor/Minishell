#include "minishell.h"

static void	pwd(void)
{
	char	pwd[256];

	if (getcwd(pwd, sizeof(pwd)) != NULL)
		printf("%s\n", pwd);
	else
		perror("getcwd() error");
}

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

static int	ft_strcmp(const char *s1, const char *s2)
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

static bool	is_build_in(char *cmd)
{
	int	i;

	i = 0;
	const char *built_in[] = {"cat", "cd", "pwd", "export", "unset", "env", NULL};

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
	if (!ft_strncmp(parser->parser_cmd, "cat", 3))
		ft_cat(parser);
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
}
