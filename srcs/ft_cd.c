/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:33:31 by hterras           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/07/11 22:28:43 by jbarette         ###   ########.fr       */
=======
/*   Updated: 2022/07/13 14:54:10 by jbarette         ###   ########.fr       */
>>>>>>> a845f7f11c9acbb3406a384d948e11026b233926
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_parser *parser, t_env *env)
{
<<<<<<< HEAD
	char	*pwd;

	pwd = 0;
=======

>>>>>>> a845f7f11c9acbb3406a384d948e11026b233926
	if (chdir(parser->parser_args) == -1)
	{
		g_code = 1;
		printf("bash: cd: %s: No such file or directory\n", parser->parser_args);
	}
	else
	{
		g_code = 0;
		pwd = (char *)ft_calloc(sizeof(char), \
			(ft_strlen("OLDPWD=")) + 1 + ft_strlen(getcwd(NULL, 0) + 1));
		ft_strcat(pwd, "OLDPWD=");
		ft_strcat(pwd, getcwd(NULL, 0));
		ft_export(env, pwd);
		free(pwd);
	}
}
