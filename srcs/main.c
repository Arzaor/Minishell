#include "minishell.h"

static void style_prompt()
{
	int 	ret;
	char 	*term_type;
	char	*color_cap;
	char	*reset_cmd;

	term_type = getenv("TERM");
	ret = tgetent(NULL, term_type);
	color_cap = tgetstr("AF", NULL);
	tputs(tparm(color_cap, COLOR_GREEN), 1, putchar);
	reset_cmd = tgetstr("md", NULL);
	tputs(reset_cmd, 1, putchar);
}

static void	start_minishell(char **env)
{
	char	*line;
	char 	*cm_cap;
	t_env	*envp;

	envp = create_env(env);
	while (1)
	{
		style_prompt();
		line = readline(":> ");
		if(line == NULL || strcmp(line, "exit") == 0)
		{
			if(line == NULL)
			{
				int line_count = tgetnum("li");
				int col_cocunt = tgetnum("cl");
				cm_cap = tgetstr("cm", NULL);
				tputs(tgoto(cm_cap, col_cocunt + 4,line_count - 2), 1, putchar);
				printf("exit");
			}
			break;
		}
		else
		{
			if (line)
				add_history(line);
			parsing_symbols(line, envp);
			free(line);
		}
	}
	free(envp);
}

static void sig_handler(int signo)
{
	if(signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if(signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

int		main(int argc, char **argv,char **env)
{
	(void)argc;
	(void)argv;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	start_minishell(env);
	return (0);
}