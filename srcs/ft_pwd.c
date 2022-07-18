/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:47:04 by hterras           #+#    #+#             */
/*   Updated: 2022/07/18 12:39:31 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_env *env)
{
	char	pwd[256];
	char	*oldpwd;

	oldpwd = 0;
	if (getcwd(pwd, sizeof(pwd)) != NULL)
	{
		printf("%s\n", pwd);
		g_code = 0;
	}
	else
	{
		if (errno == ENOENT)
		{
			g_code = 0;
			oldpwd = get_env(env, "PWD");
			printf("%s\n", oldpwd);
			free(oldpwd);
		}
		else
		{
			perror("getcwd()");
			g_code = 1;
		}
	}
}
