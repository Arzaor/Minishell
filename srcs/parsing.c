#include "minishell.h"

static void	free_array(char **array)
{
	for (int i = 0; array[i]; i++) {
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
	array = NULL;
}

void	parsing_builtins(char *line)
{
	char	**split_line;
	t_cmd	*commands;
	int		i, j, k, h;

	split_line = ft_split(line, ' ');
	commands = malloc(sizeof(t_cmd));
	commands->cmd = malloc(sizeof(char) * ft_strlen(split_line[0]) + 1);
	commands->cmd = &split_line[0];

	i = 1;
	j = 0;
	while (split_line[i])
	{
		if (split_line[i][0] == '-')
			j++;
		i++;
	}
	commands->opts = malloc(sizeof(char *) * i + 1);
	i = 1;
	j = 0;
	k = 0;
	h = 0;
	while (split_line[i])
	{
		if (split_line[i][0] == '-')
		{
			commands->opts[k] = malloc(sizeof(char) * ft_strlen(split_line[i]) + 1);
			while (split_line[i][j])
			{
				commands->opts[k][h] = split_line[i][j];
				h++;
				j++;
			}
			k++;
		}
		i++;
		j = 0;
		h = 0;
	}
	/*
	printf("%s ", commands->cmd[0]);
	i = 0;
	while (commands->opts[i])
		printf("%s ", commands->opts[i++]);
	printf("\n");
	*/
	free_array(commands->cmd);
	free_array(commands->opts);
	free(commands);
}