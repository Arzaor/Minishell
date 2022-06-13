#include "minishell.h"

void	display_prompt()
{
	char	*line;

	line = readline(":> ");
	if (line)
		add_history(line);
}

int		main(void)
{
	while (1)
	{
		// Hamza : Ajout des signaux
		display_prompt();
	}

	return 0;
}
