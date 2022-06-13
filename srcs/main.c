#include "minishell.h"

void prompt()
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

void	start_minishell()
{
	char	*line;
	char 	*cm_cap;
	
	while (1)
	{
		prompt();
		line = readline(":> ");
		if(line == NULL || strcmp(line, "exit") == 0)
		{
			if(line == NULL)
			{
				cm_cap = tgetstr("cm", NULL);
				tputs(tgoto(cm_cap, 3,4), 1, putchar);
				printf("exit");
			}
			break;
		}
		else
		{
			if (line)
				add_history(line);
			free(line);
		}	
	}
}

void sig_handler(int signo)
{
	if(signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("",0);
		rl_redisplay();
	}
	else if(signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

int		main(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	start_minishell();
	return 0;
}