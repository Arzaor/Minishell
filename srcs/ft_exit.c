/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 02:09:25 by jbarette          #+#    #+#             */
/*   Updated: 2022/07/05 14:51:06 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_parser *parser)
{
	int		i;
	int		k;
	char	*code;
	char	**split_arg;

	i = 0;
	k = 0;
	code = 0;
	split_arg = NULL;
	if (parser->parser_args)
	{
		split_arg = ft_split(parser->parser_args, ' ');
		if (split_arg[1])
		{
			printf("%s: too many arguments\n", parser->parser_cmd);
			g_code = 1;
		}
		else
		{
			if (ft_isnum(parser->parser_args[0]))
			{
				printf("exit");
				while (ft_isnum(parser->parser_args[i]))
					i++;
				code = malloc(sizeof(char) * i + 1);
				i = 0;
				while (ft_isnum(parser->parser_args[i]))
					code[k++] = parser->parser_args[i++];
				g_code = ft_atoi(code);
				free(code);
			}
			else
			{
				g_code = 255;
				printf("exit\n");
				printf("exit: %s: numeric argument required\n", parser->parser_args);
			}
		}
	}
	else
		printf("exit");
	free_parser(parser);
	exit(g_code);
}

void ft_exit_with_line2(char *line)
{
	int		line_count;
	int		col_cocunt;
	char	*cm_cap;

	line_count = tgetnum("li");
	col_cocunt = tgetnum("cl");
	cm_cap = tgetstr("cm", NULL);
	tputs(tgoto(cm_cap, col_cocunt, line_count - 1), 1, putchar);
	printf("\e[2K");
	rl_on_new_line();
	rl_redisplay();
	free(line);
	printf(":> exit");
	exit(EXIT_SUCCESS);
}

void	ft_exit_with_line(char *line)
{
	int		line_count;
	int		col_cocunt;
	char	*cm_cap;

	line_count = tgetnum("li");
	col_cocunt = tgetnum("cl");
	cm_cap = tgetstr("cm", NULL);
	tputs(tgoto(cm_cap, col_cocunt + 4, line_count-2), 1, putchar);
	free(line);
	printf("exit");
	exit(EXIT_SUCCESS);
}
