/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 02:09:25 by jbarette          #+#    #+#             */
/*   Updated: 2022/08/02 23:41:43 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exit2(t_parser *parser)
{
	char	*code;
	int		k;
	int		i;

	code = 0;
	k = 0;
	i = 0;

	while (ft_isnum(parser->parser_args[i]))
		i++;
	code = malloc(sizeof(char) * i + 1);
	i = 0;
	while (ft_isnum(parser->parser_args[i]))
		code[k++] = parser->parser_args[i++];
	g_code = ft_atoi(code);
	free(code);
	printf("exit");
	free_parser(parser);
	exit(g_code);
}

static int	check_num_for_exit(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != ' ')
	{
		if (!(ft_isnum(arg[i])))
			return (1);
		i++;
	}
	return (0);
}

static int	count_number_of_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(t_parser *parser)
{
	int		i;
	char	**split_arg;

	i = 0;
	split_arg = NULL;
	if (parser->parser_args)
	{
		if (check_num_for_exit(parser->parser_args))
		{
			printf("exit\n");
			printf("bash: exit: %s: numeric argument required\n", \
				parser->parser_args);
			g_code = 255;
			free_parser(parser);
			exit(g_code);
		}
		else if (count_number_of_arg(parser->parser_args))
		{
			printf("bash: %s: too many arguments\n", parser->parser_cmd);
			g_code = 1;
		}
		else
			ft_exit2(parser);
	}
	else
	{
		printf("exit");
		free_parser(parser);
		exit(g_code);
	}
}

void	ft_exit_with_line(char *line)
{
	int		line_count;
	int		col_cocunt;
	char	*cm_cap;

	line_count = tgetnum("li");
	col_cocunt = tgetnum("cl");
	cm_cap = tgetstr("cm", NULL);
	tputs(tgoto(cm_cap, col_cocunt + 4, line_count - 2), 1, putchar);
	free(line);
	printf("exit");
	exit(0);
}
