#include "minishell.h"

static void	pwd(void)
{
	char	pwd[256];

	if (getcwd(pwd, sizeof(pwd)) != NULL)
		printf("%s\n", pwd);
	else
		perror("getcwd() error");
}

static void	ft_env(t_env *env)
{
	display_linked_list(env);
}

char	*get_env(t_env *env, char *search)
{
	char	**tab_env;
	char	**path;
	char	*path_def;
	int		i, k;

	tab_env = create_tab(env);
	i = 0;
	k = 0;
	path = NULL;
	path_def = 0;
	while (tab_env[i])
	{
		if (ft_strncmp(search, tab_env[i], ft_strlen(search)) == 0)
			break ;
		i++;
	}
	if (tab_env[i])
	{
		path = ft_split(tab_env[i], '=');
		i = 0;
		path_def = malloc(sizeof(char) * ft_strlen(path[1]) + 1);
		while (path[1][i])
			path_def[k++] = path[1][i++];
		free_array(path);
	}
	free(tab_env);
	return (path_def);
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

void	create_cmd(t_parser *parser, t_env *env)
{
	if (!ft_strncmp(parser->parser_cmd, "echo", 4))
		ft_echo(parser, env);
	if (!ft_strncmp(parser->parser_cmd, "cd", 2))
		ft_cd(parser);
	if (!ft_strncmp(parser->parser_cmd, "pwd", 3))
		pwd();
	if (!ft_strncmp(parser->parser_cmd, "export", 6))
		ft_export(env, parser->parser_args);
	if (!ft_strncmp(parser->parser_cmd, "unset", 5))
		ft_unset(env, parser->parser_args);
	if (!ft_strncmp(parser->parser_cmd, "env", 3))
		ft_env(env);
}

static void	get_absolute_path(char *path, t_parser *parser)
{
	char	**path_split;
	int		i;
	char	*bin;

	i = 0;
	path_split = ft_split(path, ':');
	free (path);
	while (path_split[i])
	{
		bin = ft_calloc(sizeof(char), (strlen(path_split[i]) + 1 + strlen(parser->parser_cmd) + 1));
		if (bin == NULL)
			break ;
		strcat(bin, path_split[i]);
		strcat(bin, "/");
		strcat(bin, parser->parser_cmd);
		if (access(bin, F_OK) == 0)
			break ;
		free(bin);
		bin = NULL;
		i++;
	}
	free_array(path_split);
	if (bin)
		parser->parser_cmd = bin;
}

static void	exec_cmd(t_parser *parser, char **cmds)
{
	pid_t	pid = 0;
	int		status = 0;

	pid = fork();
	if (pid == -1)
		printf("Fork");
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		if (execve(parser->parser_cmd, cmds, NULL) == -1)
			printf("bash: %s: command not found\n", cmds[0]);
		exit(0);
	}
}

static void	clean_redir(t_parser *parser, int saveout1)
{
	if (parser->parser_left_redir == 1)
		dup2(saveout1, 0);
	if (parser->parser_right_redir == 2)
		dup2(saveout1, 1);
	if (parser->parser_dleft_redir == 3 && !ft_strcmp(parser->parser_cmd, "/bin/cat"))
		dup2(saveout1, 0);
	if(parser->parser_dright_redir == 4)
		dup2(saveout1, 1);
}


int handler_left_redir(t_parser *parser, char *heredoc)
{
	int		saveout1;
	int		fd;
	fd = open(heredoc, O_RDONLY);
	saveout1 = dup(0);
	close(0);
	if(fd == -1)
		printf("bash: %s: No such file or directory\n", heredoc);
	else
		dup2(fd, 0);
	return (saveout1);
}

void	handler_redir(t_parser *parser, char **cmds,t_env *env)
{
	int saveout1 = 0;
	int i = 0;

	if (parser->parser_left_redir == 1)
		saveout1 = handler_left_redir(parser, parser->parser_heredoc);
	if (parser->parser_right_redir == 2)
		saveout1 = handler_right_redir(parser);
	if (parser->parser_dleft_redir == 3)
		saveout1 = handler_dleft_redir(parser);
	if (parser->parser_dright_redir == 4)
		saveout1 = handler_dright_redir(parser);
	if (is_build_in(parser->parser_cmd))
		create_cmd(parser,env);
	else
		exec_cmd(parser, cmds);
	clean_redir(parser, saveout1);
}

int handler_dleft_redir(t_parser *parser)
{
	char	*line;
	int		saveout1;
	
	saveout1 = open("heredoc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if(saveout1 == -1)
		printf("fff");
	while ((line = readline("> ")))
	{
		if(!ft_strcmp(parser->parser_heredoc, line))
			break;
		write(saveout1,line, ft_strlen(line));
		write(saveout1, "\n",1);
		free(line);
	}
	if(!ft_strcmp(parser->parser_cmd, "/bin/cat"))
	{
		saveout1 = handler_left_redir(parser, "heredoc.txt");
		return (saveout1);
	}
	return(0);
}

int handler_dright_redir(t_parser *parser)
{
	int		saveout1;
	
	saveout1 = dup(1);
	close(1);
	dup2(open(parser->parser_heredoc, O_CREAT | O_RDWR | O_APPEND, 0666), 1);
	return (saveout1);
}

int handler_right_redir(t_parser *parser)
{
	int		saveout1;
	int		fd;
	fd = open(parser->parser_heredoc, O_RDWR);
	saveout1 = dup(1);
	close(1);
	if(fd == -1)
		dup2(open(parser->parser_heredoc, O_CREAT | O_RDWR, 0666), 1);
	else
		dup2(open(parser->parser_heredoc, O_TRUNC | O_RDWR, 0666), 1);
	return (saveout1);
}

void	handler_cmd(t_parser *parser, t_env *env, char **cmds)
{
	if (!is_build_in(parser->parser_cmd) && cmds[0][0] != '/' && ft_strncmp(cmds[0], "./", 2) != 0)
		get_absolute_path(get_env(env, "PATH"), parser);
	handler_redir(parser, cmds, env);
}
