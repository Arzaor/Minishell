#include "minishell.h"

void	start_minishell()
{
	char	*line;

	while (1)
	{
		line = readline(":> ");
		if(strcmp(line,"exit") == 0)
				break;
		printf("%s",line);
	}
}

void crtl_c(){
	
	int ret;
	int column;
	int  line_count;4
	char *term_type;
	char *cm_cap;
	column = tgetnum("co");
	line_count= tgetnum("li");

	term_type = getenv("TERM");
	//tputs (cl_cap, 1, putchar);
	ret = tgetent(NULL,term_type);
	cm_cap = tgetstr("cm", NULL);
	printf("\n");
	tputs(tgoto(cm_cap,1,1),1,putchar);
	rl_on_new_line();
	rl_redisplay();
   //printf("\n");
	
}

int		main(void)
{
	
	// Hamza : Ajout des signaux
	signal(SIGINT, crtl_c);
	start_minishell();

	return 0;
}
