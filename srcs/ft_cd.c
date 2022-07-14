/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hterras <hterras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:33:31 by hterras           #+#    #+#             */
/*   Updated: 2022/07/14 13:44:46 by hterras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_parser *parser, t_env *env)
{
	char	*pwd;
	char	pwds[256];

	pwd = 0;
	if (chdir(parser->parser_args) == -1)
	{
		g_code = 1;
		printf("bash: cd: %s: No such file or directory\n", parser->parser_args);
	}
	else
	{
		g_code = 0;
		pwd = (char *)ft_calloc(sizeof(char), (ft_strlen("OLDPWD=") + 1 \
				+ ft_strlen(getcwd(pwds, sizeof(pwds))) + 1));
		ft_strcat(pwd, "OLDPWD=");
		ft_strcat(pwd, getcwd(pwds, sizeof(pwds)));
		ft_export(env, pwd);
		free(pwd);
	}
}
