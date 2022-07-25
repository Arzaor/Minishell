/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hterras <hterras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:33:31 by hterras           #+#    #+#             */
/*   Updated: 2022/07/21 18:14:08 by hterras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cd2(char pwds[256], char *pwd, t_env *env)
{
	if (getcwd(pwds, sizeof(pwds)) != NULL)
	{
		g_code = 0;
		pwd = (char *)ft_calloc(sizeof(char), (ft_strlen("PWD=") + 1 \
				+ ft_strlen(getcwd(pwds, sizeof(pwds))) + 1));
		ft_strcat(pwd, "PWD=");
		ft_strcat(pwd, getcwd(pwds, sizeof(pwds)));
		ft_export(env, pwd);
		free(pwd);
	}
	else
		printf("cd: error retrieving current directory: getcwd: \
			cannot access parent directories: No such file or directory\n");
}

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
			printf("bash: cd: %s: No such file or \
				directory\n", parser->parser_args);
		}
		else
			ft_cd2(pwds, pwd, env);
	}
	else
	{
		pwd = get_env(env, "HOME");
		chdir(pwd);
		free(pwd);
	}
}
