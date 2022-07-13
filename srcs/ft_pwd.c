/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:47:04 by hterras           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/07/11 22:32:57 by jbarette         ###   ########.fr       */
=======
/*   Updated: 2022/07/07 16:26:00 by jbarette         ###   ########.fr       */
>>>>>>> a845f7f11c9acbb3406a384d948e11026b233926
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD
void	pwd(t_env *env)
=======
void	pwd(t_parser *parser)
>>>>>>> a845f7f11c9acbb3406a384d948e11026b233926
{
	char	pwd[256];

	if (getcwd(pwd, sizeof(pwd)) != NULL)
	{
		printf("%s\n", pwd);
		g_code = 0;
	}
	else
	{
<<<<<<< HEAD
		if (errno == ENOENT)
		{
			g_code = 0;
			printf("%s\n", get_env(env, "OLDPWD"));
		}
		else
		{
			perror("getcwd()");
			g_code = 1;
		}
=======
		printf("%s\n", parser->parser_pwd);
		// perror("getcwd()");
		g_code = 1;
>>>>>>> a845f7f11c9acbb3406a384d948e11026b233926
	}
}
