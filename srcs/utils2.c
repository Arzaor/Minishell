/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:52:59 by hterras           #+#    #+#             */
/*   Updated: 2022/08/07 15:18:25 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show_prompt(char *line, t_env *envp)
{
	t_parser	*parser;

	parser = init();
	if (line)
		add_history(line);
	parsing_handler(parser, line, envp);
}

void	style_prompt(void)
{
	char	*term_type;
	char	*color_cap;
	char	*reset_cmd;

	term_type = getenv("TERM");
	tgetent(NULL, term_type);
	color_cap = tgetstr("AF", NULL);
	tputs(tparm(color_cap, COLOR_GREEN), 1, putchar);
	reset_cmd = tgetstr("md", NULL);
	tputs(reset_cmd, 1, putchar);
}

char	send_quote(char *line, int i)
{
	int	a;

	a = 0;
	while (a < i)
	{
		if (line[a] == '\'' || line[a] == '"')
			return (line[a]);
		a++;
	}
	return (0);
}

int	ft_isalnum(int c)
{
	if (((c >= 'a') && (c <= 'z'))
		|| ((c >= 'A') && (c <= 'Z'))
		|| ((c >= '0') && (c <= '9')))
		return (1);
	return (0);
}

int	char_is_var_attribution(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(ft_isalnum(str[i])) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
