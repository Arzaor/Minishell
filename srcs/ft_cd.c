/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:33:31 by hterras           #+#    #+#             */
/*   Updated: 2022/07/19 17:47:53 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_parser *parser, t_env *env)
{
	char	*pwd;
	char	pwds[256];

	pwd = 0;
	if (parser->parser_args)
	{
		if (chdir(parser->parser_args) == -1)
		{
			g_code = 1;
			printf("bash: cd: %s: No such file or directory\n", parser->parser_args);
		}
		else
		{
			g_code = 0;
			pwd = (char *)ft_calloc(sizeof(char), (ft_strlen("PWD=") + 1 \
					+ ft_strlen(getcwd(pwds, sizeof(pwds))) + 1));
			ft_strcat(pwd, "PWD=");
			ft_strcat(pwd, getcwd(pwds, sizeof(pwds)));
			ft_export(env, pwd);
			free(pwd);
		}
	}
	else
		chdir(get_env(env, "HOME"));
}
