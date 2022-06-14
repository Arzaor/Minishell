#include "minishell.h"

static void pwd()
{
	char pwd[256];

	if (getcwd(pwd, sizeof(pwd)) != NULL)
		printf("Current working dir: %s\n", pwd);
	else
		perror("getcwd() error");
}

static void ft_env(char **env)
{
	int i;

	i = 0;
	while(env[i])
	{
		printf("%s\n",env[i]);
		i++;
	}
}

void  handler_cmd(t_parser *parser,char **env)
{
	if(!ft_strncmp(parser->parser_cmd,"cat",3))
		printf("cat");
	if(!ft_strncmp(parser->parser_cmd,"cd",2))
		printf("cd");
	if(!ft_strncmp(parser->parser_cmd,"pwd",3))
		pwd();
	if(!ft_strncmp(parser->parser_cmd,"export",6))
		printf("export");
	if(!ft_strncmp(parser->parser_cmd,"unset",5))
		printf("unset");
	if(!ft_strncmp(parser->parser_cmd,"env",3))
		ft_env(env);
}
