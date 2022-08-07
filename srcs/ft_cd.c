/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:33:31 by hterras           #+#    #+#             */
/*   Updated: 2022/08/07 14:21:23 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cd2(char *pwd, t_env *env)
{
	char	pwds[256];
	char	*oldpwd_env;
	char	*oldpwd;

	oldpwd_env = 0;
	oldpwd = 0;
	if (getcwd(pwds, sizeof(pwds)) != NULL)
	{
		g_code = 0;
		oldpwd_env = get_env(env, "PWD");
		oldpwd = (char *)ft_calloc(sizeof(char), (ft_strlen("OLDPWD=") + 1 + ft_strlen(oldpwd_env) + 1));
		ft_strcat(oldpwd, "OLDPWD=");
		ft_strcat(oldpwd, oldpwd_env);
		ft_export(env, oldpwd);
		pwd = (char *)ft_calloc(sizeof(char), (ft_strlen("PWD=") + 1 \
				+ ft_strlen(getcwd(pwds, sizeof(pwds))) + 1));
		ft_strcat(pwd, "PWD=");
		ft_strcat(pwd, getcwd(pwds, sizeof(pwds)));
		ft_export(env, pwd);
		free(oldpwd);
		free(oldpwd_env);
		free(pwd);
	}
	else
		printf("cd: error retrieving current directory: getcwd: \
cannot access parent directories: No such file or directory\n");
}

void	ft_cd(t_parser *parser, t_env *env)
{
	char	*pwd;

	pwd = 0;
	if (parser->parser_args)
	{
		if (chdir(parser->parser_args) == -1)
		{
			g_code = 1;
			printf("bash: cd: %s: No such file \
or directory\n", parser->parser_args);
		}
		else
			ft_cd2(pwd, env);
	}
	else
	{
		pwd = get_env(env, "HOME");
		chdir(pwd);
		free(pwd);
	}
}
