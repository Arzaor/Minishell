#include "minishell.h"

void	start_minishell()
{
	char	*line;

	while (1)
	{
		line = readline(":> ");
		if (line)
			add_history(line);
		parsing_builtins(line);
	}
}

int		main(void)
{
	// Hamza : Ajout des signaux
	start_minishell();

	return 0;
}
